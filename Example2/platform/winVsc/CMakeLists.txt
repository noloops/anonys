cmake_minimum_required(VERSION 3.20)

project(Example2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Root of the repository (three levels up from this CMakeLists.txt)
set(REPO_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../../..")

# Global include directories
include_directories(
    "${CMAKE_CURRENT_SOURCE_DIR}/config"
    "${REPO_ROOT}/Example2/src"
    "${REPO_ROOT}/ext"
)

# All source files for the single executable
add_executable(Example2
    # Platform entry point
    src/main.cpp

    # Core framework
    "${REPO_ROOT}/ext/anonys/FsmCore.cpp"
    "${REPO_ROOT}/ext/anonys/calcMaxBuffer.cpp"

    # Application sources
    "${REPO_ROOT}/Example2/src/anonys/FsmPool.cpp"
    "${REPO_ROOT}/Example2/src/anonys/BufferCalc.cpp"
    "${REPO_ROOT}/Example2/src/Fsm/Elevator/Idle.cpp"
    "${REPO_ROOT}/Example2/src/Fsm/Elevator/Moving.cpp"
    "${REPO_ROOT}/Example2/src/Fsm/Elevator/Moving/GoingUp.cpp"
    "${REPO_ROOT}/Example2/src/Fsm/Elevator/Moving/GoingUp/Accelerating.cpp"
    "${REPO_ROOT}/Example2/src/Fsm/Elevator/Moving/GoingUp/Accelerating/FullSpeed.cpp"
    "${REPO_ROOT}/Example2/src/Fsm/Elevator/Moving/GoingUp/Decelerating.cpp"
    "${REPO_ROOT}/Example2/src/Fsm/Elevator/Moving/GoingDown.cpp"
    "${REPO_ROOT}/Example2/src/Fsm/Elevator/Stopped.cpp"
    "${REPO_ROOT}/Example2/src/Fsm/TrafficLight/Off.cpp"
    "${REPO_ROOT}/Example2/src/Fsm/TrafficLight/Operating.cpp"
    "${REPO_ROOT}/Example2/src/Fsm/TrafficLight/Operating/Green.cpp"
    "${REPO_ROOT}/Example2/src/Fsm/TrafficLight/Operating/Yellow.cpp"
    "${REPO_ROOT}/Example2/src/Fsm/TrafficLight/Operating/Red.cpp"
    "${REPO_ROOT}/Example2/src/Fsm/TrafficLight/Flashing.cpp"
    "${REPO_ROOT}/Example2/src/Fsm/Washer/Idle.cpp"
    "${REPO_ROOT}/Example2/src/Fsm/Washer/Running.cpp"
    "${REPO_ROOT}/Example2/src/Fsm/Washer/Running/Filling.cpp"
    "${REPO_ROOT}/Example2/src/Fsm/Washer/Running/Washing.cpp"
    "${REPO_ROOT}/Example2/src/Fsm/Washer/Running/Washing/Agitating.cpp"
    "${REPO_ROOT}/Example2/src/Fsm/Washer/Running/Washing/Soaking.cpp"
    "${REPO_ROOT}/Example2/src/Fsm/Washer/Running/Draining.cpp"
    "${REPO_ROOT}/Example2/src/Fsm/Washer/Done.cpp"
    "${REPO_ROOT}/Example2/src/Fsm/Washer/Error.cpp"
    "${REPO_ROOT}/Example2/src/Fsm/Washer/Halted.cpp"
)
