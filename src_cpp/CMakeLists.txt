
# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)

# Collect all the source files in the current directory and the source directories
file(GLOB_RECURSE SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/*.cpp
)

# Collect all header files in the current directory and the include directories
file(GLOB_RECURSE HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/../include_cpp/*.hpp
)

# Add the executable and link the sources
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Link the hardware abstraction layer
target_link_libraries(${PROJECT_NAME} PRIVATE hal)

# Specify include directories for the target
target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/../include_cpp
)

# Ensure C++17 is used
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
