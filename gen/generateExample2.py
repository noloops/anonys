"""Generate code for Example2 (Elevator, TrafficLight, Washer FSMs)."""

from pathlib import Path
from anonys_gen.generator import GeneratorConfig, generate

SCRIPT_DIR = Path(__file__).parent

config = GeneratorConfig(
    fsm_definitions=[
        SCRIPT_DIR / "../Example2/fsmDef/Elevator.txt",
        SCRIPT_DIR / "../Example2/fsmDef/TrafficLight.txt",
        SCRIPT_DIR / "../Example2/fsmDef/Washer.txt",
    ],
    anonys_output_dir=SCRIPT_DIR / "../Example2/src",
    fsm_output_dir=SCRIPT_DIR / "../Example2/src/Fsm",
    include_guard_prefix="EXAMPLE2",
)

generate(config)
print("Example2 code generation complete.")
