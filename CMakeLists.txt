# Project root folder
cmake_minimum_required(VERSION 2.8)

project(simwar)

# Set up build folder structure
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

# Set up source subfolders
add_subdirectory("${PROJECT_SOURCE_DIR}/src") # main source
add_subdirectory("${PROJECT_SOURCE_DIR}/resources") # resources
add_subdirectory("${PROJECT_SOURCE_DIR}/config") # config
add_subdirectory("${PROJECT_SOURCE_DIR}/lib") # libraries
