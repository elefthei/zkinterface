extern crate serde;
extern crate serde_json;
extern crate zkinterface;

use std::fs;
use std::io::{stdin, stdout, Read, Write, copy};
use std::path::{Path, PathBuf};
use structopt::StructOpt;

use zkinterface::{
    reading::Messages,
    MessagesOwned,
    stats::Stats,
    Result,
};
use std::fs::{File, create_dir_all};
use std::ffi::OsStr;

const ABOUT: &str = "
This is a collection of tools to work with zero-knowledge statements encoded in zkInterface messages.

The tools below work within a workspace directory given after the tool name (`local` in the examples below), or in the current working directory by default. To read from stdin or write to stdout, pass a dash - instead of a filename.

Create an example statement:
    zkif example local
Or:
    zkif example - > local/example.zkif

Print a statement in different forms:
    zkif json    local
    zkif pretty  local
    zkif explain local

Simulate a proving system:
    zkif stats       local
    zkif fake_prove  local
    zkif fake_verify local

Write all the statement files to stdout (to pipe to another program):
    zkif cat local

";

use structopt::clap::AppSettings::*;

#[derive(Debug, StructOpt)]
#[structopt(
name = "zkif",
about = "zkInterface toolbox.",
long_about = ABOUT,
setting(DontCollapseArgsInUsage),
setting(ColoredHelp)
)]
struct Options {
    /// Which tool to run.
    ///
    /// example     Create example circuits.
    ///
    /// cat         Write .zkif files to stdout.
    ///
    /// json        Convert to JSON on a single line.
    ///
    /// pretty      Convert to JSON with spacing.
    ///
    /// explain     Print the content in a human-readable form.
    ///
    /// stats       Calculate statistics about the circuit.
    #[structopt(default_value = "help")]
    tool: String,

    /// The tools work in a workspace directory containing .zkif files.
    ///
    /// Alternatively, a list of .zkif files can be provided explicitly.
    ///
    /// The dash - means either write to stdout or read from stdin.
    #[structopt(default_value = ".")]
    paths: Vec<PathBuf>,

    /// Select a profile: R1CS or AC (Arithmetic Circuit).
    #[structopt(short, long, default_value = "R1CS")]
    profile: String,
}

fn main() -> Result<()> {
    let options: Options = Options::from_args();

    match &options.tool[..] {
        "example" => main_example(&options),
        "cat" => main_cat(&options),
        "json" => main_json(&load_messages(&options)?),
        "pretty" => main_pretty(&load_messages(&options)?),
        "explain" => main_explain(&load_messages(&options)?),
        "stats" => main_stats(&load_messages(&options)?),
        "fake_prove" => main_fake_prove(&load_messages(&options)?),
        "fake_verify" => main_fake_verify(&load_messages(&options)?),
        "help" => {
            Options::clap().print_long_help()?;
            eprintln!("\n");
            Ok(())
        }
        _ => {
            Options::clap().print_long_help()?;
            eprintln!("\n");
            Err(format!("Unknown command {}", &options.tool).into())
        }
    }
}


fn load_messages(opts: &Options) -> Result<Messages> {
    let mut messages = Messages::new();

    for path in list_files(opts)? {
        if path == Path::new("-") {
            eprintln!("Loading from stdin");
            messages.read_from(&mut stdin())?;
        } else {
            eprintln!("Loading file {}", path.display());
            messages.read_file(path)?;
        }
    }

    Ok(messages)
}

fn list_files(opts: &Options) -> Result<Vec<PathBuf>> {
    let mut all_paths = vec![];

    for arg in &opts.paths {
        if arg.extension() == Some(OsStr::new("zkif")) {
            all_paths.push(arg.clone());
        } else {
            for file in fs::read_dir(arg)? {
                match file {
                    Ok(file) => {
                        if file.path().extension() == Some(OsStr::new("zkif")) {
                            all_paths.push(file.path());
                        }
                    }
                    Err(err) => {
                        eprintln!("Warning: {}", err);
                        continue;
                    }
                }
            }
        }
    }
    Ok(all_paths)
}

fn main_example(opts: &Options) -> Result<()> {
    use zkinterface::examples::*;

    if opts.paths.len() != 1 {
        return Err("Specify a single directory where to write examples.".into());
    }
    let out_dir = &opts.paths[0];

    if out_dir == Path::new("-") {
        example_circuit_header().write_into(&mut stdout())?;
        write_example_constraints(stdout())?;
        write_example_witness(stdout())?;
    } else {
        if out_dir.ends_with(".zkif") { return Err("Expecting to write to a directory, not to a file.".into()); }

        create_dir_all(out_dir)?;

        example_circuit_header().write_into(
            &mut File::create(out_dir.join("main.zkif"))?)?;

        write_example_constraints(
            File::create(out_dir.join("constraints.zkif"))?)?;

        write_example_witness(
            File::create(out_dir.join("witness.zkif"))?)?;

        eprintln!("Written {}", out_dir.join("*.zkif").display());
    }

    Ok(())
}


fn main_cat(opts: &Options) -> Result<()> {
    for path in list_files(opts)? {
        let mut file = File::open(&path)?;
        let mut stdout = stdout();
        copy(&mut file, &mut stdout)?;
    }
    Ok(())
}

fn main_json(messages: &Messages) -> Result<()> {
    let messages_owned = MessagesOwned::from(messages);
    serde_json::to_writer(stdout(), &messages_owned)?;
    Ok(())
}

fn main_pretty(messages: &Messages) -> Result<()> {
    let messages_owned = MessagesOwned::from(messages);
    serde_json::to_writer_pretty(stdout(), &messages_owned)?;
    Ok(())
}

fn main_explain(messages: &Messages) -> Result<()> {
    eprintln!("{:?}", messages);
    Ok(())
}

fn main_stats(messages: &Messages) -> Result<()> {
    let mut stats = Stats::new();
    stats.push(messages)?;
    serde_json::to_writer_pretty(stdout(), &stats)?;
    Ok(())
}


fn main_fake_prove(_: &Messages) -> Result<()> {
    let mut file = File::create("fake_proof")?;
    write!(file, "I hereby promess that I saw a witness that satisfies the constraint system.")?;
    eprintln!("Fake proof written to file `fake_proof`.");
    Ok(())
}

fn main_fake_verify(_: &Messages) -> Result<()> {
    let mut file = File::open("fake_proof")?;
    let mut proof = String::new();
    file.read_to_string(&mut proof)?;
    assert_eq!(proof, "I hereby promess that I saw a witness that satisfies the constraint system.");
    eprintln!("Fake proof verified!");
    Ok(())
}
