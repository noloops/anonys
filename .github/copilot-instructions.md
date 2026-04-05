<!-- Workspace-specific custom instructions for Copilot -->
# Anonys - C++ FSM Framework

## Project Overview
- C++ finite state machine (FSM) framework
- Platform-specific builds under Example1/platform/
- Project structure: ext/ (core framework), Example1/ (example app with platform-specific builds)

## Build (VS Code / CMake - Windows)
- Open `Example1.code-workspace` in VS Code
- Configure and build via CMake (x64 Debug)
- Platform config: `Example1/platform/winVsc/`

## Coding Conventions
- Header-only where possible for FSM definitions
- Use `.h` for headers, `.cpp` for implementations
- Namespace-based organization matching directory structure
