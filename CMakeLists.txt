cmake_minimum_required(VERSION 3.26)

# Add hardware abstraction layer
add_subdirectory(hal)

# Check if a language was specified in the presets or the environment
if (NOT PROJECT_LANGUAGE)
    message(FATAL_ERROR "No project language was specified.")
endif()

# Check the project language set in presets
if (PROJECT_LANGUAGE STREQUAL "C")
    message(STATUS "Configuring for C language")
    project(temp-monitor-c LANGUAGES C)
    add_subdirectory(src)
elseif (PROJECT_LANGUAGE STREQUAL "CXX")
    message(STATUS "Configuring for C++ language")
    project(temp-monitor-cpp LANGUAGES CXX)
    add_subdirectory(src_cpp)
endif()

