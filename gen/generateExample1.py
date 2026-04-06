"""Generate code for Example1 (Jukebox FSM)."""

from pathlib import Path
from anonys_gen.generator import GeneratorConfig, generate

SCRIPT_DIR = Path(__file__).parent

config = GeneratorConfig(
    fsm_definitions=[
        SCRIPT_DIR / ".." / "Example1" / "fsmDef" / "Jukebox.txt",
    ],
    anonys_output_dir=str(SCRIPT_DIR / ".." / "Example1" / "src"),
    fsm_output_dir=str(SCRIPT_DIR / ".." / "Example1" / "src" / "Fsm"),
    project_name="EXAMPLE1",
)

generate(config)
print("Example1 code generation complete.")
