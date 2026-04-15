# Adds application sources to the main project target.
# Called via add_subdirectory from the platform CMakeLists.txt.

set(REPO_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../..")

target_sources(${CMAKE_PROJECT_NAME} PRIVATE
	# Application entry points
	${CMAKE_CURRENT_SOURCE_DIR}/example.cpp

	# Terminals
	${CMAKE_CURRENT_SOURCE_DIR}/Terminals/Led.cpp

	# anonys framework
	"${REPO_ROOT}/ext/anonys/FsmCore.cpp"
	"${REPO_ROOT}/ext/anonys/calcMaxBuffer.cpp"

	# Generated pool / buffer calculator
	${CMAKE_CURRENT_SOURCE_DIR}/anonys/FsmPool.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/anonys/BufferCalc.cpp

	# LedJuggler states
	${CMAKE_CURRENT_SOURCE_DIR}/Fsm/LedJuggler/Running.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Fsm/LedJuggler/Running/Pattern1.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Fsm/LedJuggler/Running/Pattern1/BlinkA.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Fsm/LedJuggler/Running/Pattern1/OnA.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Fsm/LedJuggler/Running/Pattern1/OffA.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Fsm/LedJuggler/Running/Pattern2.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Fsm/LedJuggler/Running/Pattern2/BlinkB.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Fsm/LedJuggler/Running/Pattern2/OnB.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Fsm/LedJuggler/Running/Pattern2/OffB.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/Fsm/LedJuggler/Running/Paused.cpp
)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}
	"${REPO_ROOT}/ext"
)
