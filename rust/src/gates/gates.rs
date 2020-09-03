use flatbuffers::{FlatBufferBuilder, WIPOffset};
use serde::{Deserialize, Serialize};
use crate::zkinterface_generated::zkinterface::{Gate, GateArgs, GateSet, GateConstant, GateConstantArgs, Wire, GateAssertZero, GateAdd2, GateMul2, GateAssertZeroArgs, GateAdd2Args, GateMul2Args, GateInstanceVar, GateInstanceVarArgs, GateWitness, GateWitnessArgs};


#[derive(Clone, Debug, Eq, PartialEq, Deserialize, Serialize)]
pub enum GateOwned {
    Constant(u64, Vec<u8>),
    InstanceVar(u64),
    Witness(u64),
    AssertZero(u64),
    Add2(u64, u64, u64),
    Mul2(u64, u64, u64),
}

impl<'a> From<Gate<'a>> for GateOwned {
    /// Convert from Flatbuffers references to owned structure.
    fn from(gate_ref: Gate) -> GateOwned {
        match gate_ref.gate_type() {
            GateSet::GateConstant => {
                let gate = gate_ref.gate_as_gate_constant().unwrap();
                GateOwned::Constant(
                    gate.output().unwrap().id(),
                    Vec::from(gate.constant().unwrap()))
            }

            GateSet::GateInstanceVar => {
                let gate = gate_ref.gate_as_gate_instance_var().unwrap();
                GateOwned::InstanceVar(
                    gate.output().unwrap().id())
            }

            GateSet::GateWitness => {
                let gate = gate_ref.gate_as_gate_witness().unwrap();
                GateOwned::Witness(
                    gate.output().unwrap().id())
            }

            GateSet::GateAssertZero => {
                let gate = gate_ref.gate_as_gate_assert_zero().unwrap();
                GateOwned::AssertZero(
                    gate.input().unwrap().id())
            }

            GateSet::GateAdd2 => {
                let gate = gate_ref.gate_as_gate_add_2().unwrap();
                GateOwned::Add2(
                    gate.output().unwrap().id(),
                    gate.left().unwrap().id(),
                    gate.right().unwrap().id())
            }

            GateSet::GateMul2 => {
                let gate = gate_ref.gate_as_gate_mul_2().unwrap();
                GateOwned::Mul2(
                    gate.output().unwrap().id(),
                    gate.left().unwrap().id(),
                    gate.right().unwrap().id())
            }

            _ => unimplemented!()
        }
    }
}

impl GateOwned {
    /// Add this structure into a Flatbuffers message builder.
    pub fn build<'bldr: 'args, 'args: 'mut_bldr, 'mut_bldr>(
        &'args self,
        builder: &'mut_bldr mut FlatBufferBuilder<'bldr>,
    ) -> WIPOffset<Gate<'bldr>>
    {
        match self {
            GateOwned::Constant(output, constant) => {
                let cons = builder.create_vector(constant);
                let gate = GateConstant::create(builder, &GateConstantArgs {
                    output: Some(&Wire::new(*output)),
                    constant: Some(cons),
                });
                Gate::create(builder, &GateArgs {
                    gate_type: GateSet::GateConstant,
                    gate: Some(gate.as_union_value()),
                })
            }

            GateOwned::InstanceVar(output) => {
                let gate = GateInstanceVar::create(builder, &GateInstanceVarArgs {
                    output: Some(&Wire::new(*output)),
                });
                Gate::create(builder, &GateArgs {
                    gate_type: GateSet::GateInstanceVar,
                    gate: Some(gate.as_union_value()),
                })
            }

            GateOwned::Witness(output) => {
                let gate = GateWitness::create(builder, &GateWitnessArgs {
                    output: Some(&Wire::new(*output)),
                });
                Gate::create(builder, &GateArgs {
                    gate_type: GateSet::GateWitness,
                    gate: Some(gate.as_union_value()),
                })
            }

            GateOwned::AssertZero(input) => {
                let gate = GateAssertZero::create(builder, &GateAssertZeroArgs {
                    input: Some(&Wire::new(*input)),
                });
                Gate::create(builder, &GateArgs {
                    gate_type: GateSet::GateAssertZero,
                    gate: Some(gate.as_union_value()),
                })
            }

            GateOwned::Add2(output, left, right) => {
                let gate = GateAdd2::create(builder, &GateAdd2Args {
                    output: Some(&Wire::new(*output)),
                    left: Some(&Wire::new(*left)),
                    right: Some(&Wire::new(*right)),
                });
                Gate::create(builder, &GateArgs {
                    gate_type: GateSet::GateAdd2,
                    gate: Some(gate.as_union_value()),
                })
            }

            GateOwned::Mul2(output, left, right) => {
                let gate = GateMul2::create(builder, &GateMul2Args {
                    output: Some(&Wire::new(*output)),
                    left: Some(&Wire::new(*left)),
                    right: Some(&Wire::new(*right)),
                });
                Gate::create(builder, &GateArgs {
                    gate_type: GateSet::GateMul2,
                    gate: Some(gate.as_union_value()),
                })
            }
        }
    }
}