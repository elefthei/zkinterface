//
// @author Aurélien Nicolas <aurel@qed-it.com>
// @date 2019

use std::slice;
use std::error::Error;
use zkinterface::{
    reading::Messages,
    owned::circuit::CircuitOwned,
    owned::command::CommandOwned,
    owned::keyvalue::KeyValueOwned,
};

#[allow(improper_ctypes)]
extern "C" {
    fn gadgetlib_call_gadget(
        circuit_msg: *const u8,
        command_msg: *const u8,
        constraints_callback: extern fn(context_ptr: *mut Messages, message: *const u8) -> bool,
        constraints_context: *mut Messages,
        witness_callback: extern fn(context_ptr: *mut Messages, message: *const u8) -> bool,
        witness_context: *mut Messages,
        return_callback: extern fn(context_ptr: *mut Messages, message: *const u8) -> bool,
        return_context: *mut Messages,
    ) -> bool;
}

/// Collect the stream of any messages into the context.
extern "C"
fn receive_message_callback(
    context_ptr: *mut Messages,
    message_ptr: *const u8,
) -> bool {
    let (context, buf) = from_c(context_ptr, message_ptr);

    context.push_message(Vec::from(buf)).is_ok()
}


// Read a size prefix (4 bytes, little-endian).
fn read_size_prefix(ptr: *const u8) -> u32 {
    let buf = unsafe { slice::from_raw_parts(ptr, 4) };
    ((buf[0] as u32) << 0) | ((buf[1] as u32) << 8) | ((buf[2] as u32) << 16) | ((buf[3] as u32) << 24)
}

// Bring arguments from C calls back into the type system.
fn from_c<'a, CTX>(
    context_ptr: *mut CTX,
    response: *const u8,
) -> (&'a mut CTX, &'a [u8]) {
    let context = unsafe { &mut *context_ptr };

    let response_len = read_size_prefix(response) + 4;
    let buf = unsafe { slice::from_raw_parts(response, response_len as usize) };

    (context, buf)
}

pub fn call_gadget(circuit: &CircuitOwned, command: &CommandOwned) -> Result<(Messages, Messages, Messages), Box<dyn Error>> {
    let mut circuit_buf = vec![];
    circuit.write(&mut circuit_buf)?;
    let mut command_buf = vec![];
    command.write(&mut command_buf)?;

    let mut constraints_context = Messages::new(circuit.free_variable_id);
    let mut witness_context = Messages::new(circuit.free_variable_id);
    let mut return_context = Messages::new(circuit.free_variable_id);

    let ok = unsafe {
        gadgetlib_call_gadget(
            circuit_buf.as_ptr(),
            command_buf.as_ptr(),
            receive_message_callback,
            &mut constraints_context as *mut Messages,
            receive_message_callback,
            &mut witness_context as *mut Messages,
            receive_message_callback,
            &mut return_context as *mut Messages,
        )
    };

    match ok {
        true => Ok((constraints_context, witness_context, return_context)),
        false => Err("call_gadget failed".into()),
    }
}


#[test]
fn test_cpp_gadget() {
    use zkinterface::owned::variables::VariablesOwned;

    let mut subcircuit = CircuitOwned {
        connections: VariablesOwned {
            variable_ids: vec![100, 101, 102, 103], // Some input variables.
            values: None,
        },
        free_variable_id: 104,
        field_maximum: None,
        configuration: Some(vec![
            KeyValueOwned {
                key: "function".to_string(),
                text: Some("tinyram.and".to_string()),
                data: None,
                number: 0,
            }]),
    };

    {
        println!("==== R1CS generation ====");
        let command = CommandOwned { constraints_generation: true, witness_generation: false };
        let (constraints, witness, response) = call_gadget(&subcircuit, &command).unwrap();

        println!("R1CS: Rust received {} messages including {} gadget return.",
                 constraints.messages.len(),
                 constraints.circuits().len());

        assert!(constraints.messages.len() == 1);
        assert!(witness.messages.len() == 0);
        assert!(response.circuits().len() == 1);

        println!("R1CS: Got constraints:");
        for c in constraints.iter_constraints() {
            println!("{:?} * {:?} = {:?}", c.a, c.b, c.c);
        }

        let free_variable_id_after = response.last_circuit().unwrap().free_variable_id();
        println!("R1CS: Free variable id after the call: {}\n", free_variable_id_after);
        assert!(free_variable_id_after == 104 + 36);
    }

    {
        println!("==== Witness generation ====");
        // Specify input values.
        subcircuit.connections.values = Some(vec![11, 12, 9, 14 as u8]);

        let command = CommandOwned { constraints_generation: false, witness_generation: true };
        let (constraints, witness, response) = call_gadget(&subcircuit, &command).unwrap();

        println!("Assignment: Rust received {} messages including {} gadget return.",
                 witness.messages.len(),
                 witness.circuits().len());

        assert!(constraints.messages.len() == 0);
        assert!(witness.messages.len() == 1);
        assert!(response.circuits().len() == 1);

        let assignment: Vec<_> = witness.iter_witness().collect();

        println!("Assignment: Got witness:");
        for var in assignment.iter() {
            println!("{:?}", var);
        }

        assert_eq!(assignment.len(), 36);
        assert_eq!(assignment[0].id, 104 + 0); // First gadget-allocated variable.
        assert_eq!(assignment[0].value.len(), 32);
        assert_eq!(assignment[1].id, 104 + 1); // Second "
        assert_eq!(assignment[1].value.len(), 32);

        let free_variable_id_after = response.last_circuit().unwrap().free_variable_id();
        println!("Assignment: Free variable id after the call: {}", free_variable_id_after);
        assert!(free_variable_id_after == 104 + 36);

        let out_vars = response.connection_variables().unwrap();
        println!("Output variables: {:?}", out_vars);
        assert_eq!(out_vars.len(), 2);
    }
}
