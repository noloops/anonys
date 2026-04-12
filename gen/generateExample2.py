# ANONYS FINITE STATE MACHINE FRAMEWORK
# Copyright (c) 2026 Jan Hofmann <anonys@noloops.ch>
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://apache.org

"""Generate code for Example2 (Elevator, TrafficLight, Washer FSMs)."""

from pathlib import Path
import sys
from anonys_gen.generator import GeneratorConfig, generate

SCRIPT_DIR = Path(__file__).parent

try:
    config = GeneratorConfig(
        fsm_definitions=[
            SCRIPT_DIR / "../Example2/fsmDef/Elevator.txt",
            SCRIPT_DIR / "../Example2/fsmDef/TrafficLight.txt",
            SCRIPT_DIR / "../Example2/fsmDef/Washer.txt",
        ],
        anonys_output_dir=SCRIPT_DIR / "../Example2/src",
        fsm_output_dir=SCRIPT_DIR / "../Example2/src/Fsm",
        include_guard_prefix="EXAMPLE2",
        header=SCRIPT_DIR / "header.txt",
        additional_fsm_ids=["AdditionalId1", "AdditionalId2"],
    )
    generate(config)
    print("Example2 code generation complete.")
except (ValueError, TypeError) as e:
    print(f"Error: {e}", file=sys.stderr)
