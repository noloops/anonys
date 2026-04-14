# Adds application sources to the main project target.
# Called via add_subdirectory from the platform CMakeLists.txt.

target_sources(${CMAKE_PROJECT_NAME} PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/example.cpp
)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}
)
