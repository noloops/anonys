# ANONYS FINITE STATE MACHINE FRAMEWORK
# Copyright (c) 2026 Jan Hofmann <anonys@noloops.ch>
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://apache.org

"""Generate code for Example1 (Jukebox FSM)."""

from pathlib import Path
from anonys_gen.generator import GeneratorConfig, generate

SCRIPT_DIR = Path(__file__).parent

config = GeneratorConfig(
    fsm_definitions=[
        SCRIPT_DIR / "../Example1/fsmDef/Jukebox.txt",
    ],
    anonys_output_dir=SCRIPT_DIR / "../Example1/src",
    fsm_output_dir=SCRIPT_DIR / "../Example1/src/Fsm",
    include_guard_prefix="EXAMPLE1",
)

generate(config)
print("Example1 code generation complete.")
