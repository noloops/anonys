# Anonys – State Machine Framework

Anonys is a modular framework for implementing hierarchical finite state machines with structured extended state handling.

It consists of three repositories:

- Main Repository (this repository)  
  Contains:  
  - Conceptual documentation (including this document)  
  - High-level architecture  
  - Integration examples  

- anonys-core  
  Provides:  
  - The event-handling library  
  - Core runtime primitives for state machine execution  

- Code Generator Repository  
  Provides:  
  - Tooling to generate boilerplate and state machine structures  
  - Support for consistent and scalable FSM definitions  

The two supporting repositories (anonys-core and the code generator) are included in the main repository as git submodules, ensuring:

- Version alignment  
- Reproducible builds  
- Clear separation of concerns  

---

## Repository Structure

![Repository Structure](img/anonys_repository_structure.svg)

---

# Finite State Machines (FSM) – Overview

A Finite State Machine (FSM) is a computational model that represents a system as a finite set of states with transitions between them. At any point in time, the system is in exactly one state, and transitions are triggered by events or conditions.

## Core Concepts

- State: A well-defined condition or mode of the system  
- Transition: A directed edge between states, triggered by events  
- Event: An input that may cause a transition  
- Initial State: The starting point of the FSM  
- Actions: Logic executed on transitions or during state entry/exit  

FSMs are especially useful for modeling deterministic, event-driven behavior with clear control flow.

---

## Basic FSM Structure

<!-- draw.io import: fsm_basic_structure.drawio -->

---

# FSM with State-Local Stack (Extended State Model)

## Motivation

Standard FSMs lack memory beyond the current state. While extended FSMs (EFSMs) introduce variables, managing them across hierarchical states often leads to unclear ownership and implicit coupling.

This model introduces a strict LIFO stack per state machine, ensuring well-defined variable lifetime and controlled data flow.

---

## Core Concept

Each FSM instance maintains its own LIFO stack that holds extended state variables.

- Variables are pushed and popped in strict stack order  
- Variables are mutable  
- Access is granted only via explicitly passed references  
- No global or implicit shared state exists  

---

## Controlled Data Flow

- Substates cannot access the stack directly  
- Instead, parent states:  
  - Select relevant variables  
  - Pass references explicitly  

This creates:

- Clear data ownership  
- Explicit dependencies  
- Reduced coupling  

---

## Conceptual Architecture

<!-- draw.io import: fsm_stack_architecture.drawio -->

---

## Execution Model

1. Initialization  
   - FSM is instantiated  
   - Constructor initializes base variables and pushes them onto the stack  

2. State Entry  
   - State may:  
     - Push additional variables onto the stack  
     - Request references to existing variables  

3. Substate Execution  
   - Parent passes selected references  
   - Substate operates exclusively on those references  

4. State Exit  
   - State may:  
     - Execute cleanup logic  
     - Pop variables from the stack  

5. Destruction  
   - Remaining stack variables are cleaned up via destructors  

---

## Example Flow

<!-- draw.io import: fsm_stack_flow.drawio -->

---

# Terminals (Encapsulation of Extended State)

## Motivation

Directly exposing raw variables—even via references—can lead to:

- Tight coupling  
- Poor abstraction  
- Fragile interfaces  

To address this, extended state variables should be encapsulated.

---

## Definition

A Terminal is a helper class that encapsulates one or more extended state variables and exposes a clean, well-defined interface.

---

## Properties of Terminals

- Encapsulate internal data and logic  
- Provide controlled access via methods  
- Are stored on the FSM stack like any other variable  
- Are passed by reference to substates  

---

## Benefits

1. Abstraction  
   - Internal representation can change without affecting states  
   - States interact only via defined methods  

2. Safety  
   - Prevents unintended or invalid manipulation of raw data  

3. Reusability  
   - Terminals can be reused across different state machines  

4. Clarity  
   - Makes data flow and responsibilities explicit  

---

## Example Structure

<!-- draw.io import: fsm_terminals_structure.drawio -->

---

## Design Recommendation

- Prefer Terminals over primitive variables  
- Pass only the required terminals to substates  
- Keep terminal interfaces minimal and intention-revealing
