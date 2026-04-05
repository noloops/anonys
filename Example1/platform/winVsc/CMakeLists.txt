cmake_minimum_required(VERSION 3.20)

project(Example1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Root of the repository (three levels up from this CMakeLists.txt)
set(REPO_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../../..")

# Global include directories
include_directories(
    "${CMAKE_CURRENT_SOURCE_DIR}/config"
    "${REPO_ROOT}/Example1/src"
    "${REPO_ROOT}/ext"
)

# All source files for the single executable
add_executable(Example1
    # Platform entry point
    src/main.cpp

    # Core framework
    "${REPO_ROOT}/ext/anonys/FsmCore.cpp"

    # Application sources
    "${REPO_ROOT}/Example1/src/anonys/FsmPool.cpp"
    "${REPO_ROOT}/Example1/src/env/TestLog.cpp"
    "${REPO_ROOT}/Example1/src/env/TestEventSenderService.cpp"
    "${REPO_ROOT}/Example1/src/env/TestTimerService.cpp"
    "${REPO_ROOT}/Example1/src/env/TestTracingService.cpp"
    "${REPO_ROOT}/Example1/src/env/Helper.cpp"
    "${REPO_ROOT}/Example1/src/env/Expected.cpp"
    "${REPO_ROOT}/Example1/src/env/Executor.cpp"
    "${REPO_ROOT}/Example1/src/env/Tester.cpp"
    "${REPO_ROOT}/Example1/src/Fsm/Jukebox/Off.cpp"
    "${REPO_ROOT}/Example1/src/Fsm/Jukebox/Idle.cpp"
    "${REPO_ROOT}/Example1/src/Fsm/Jukebox/Playing.cpp"
    "${REPO_ROOT}/Example1/src/Fsm/Jukebox/Playing/Normal.cpp"
    "${REPO_ROOT}/Example1/src/Fsm/Jukebox/Playing/Paused.cpp"
    "${REPO_ROOT}/Example1/src/Fsm/Jukebox/Error.cpp"
)
