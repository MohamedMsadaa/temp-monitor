
# Set C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED YES)

# Collect all the source files in the current directory and source directories
file(GLOB_RECURSE SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/*.c
)

# Collect all header files in the include directories
file(GLOB_RECURSE HEADERS
    ${CMAKE_CURRENT_LIST_DIR}/../include/*.h
)

# Add the executable and link the sources
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Link the hardware abstraction layer (HAL)
target_link_libraries(${PROJECT_NAME} PRIVATE hal)

# Specify include directories for the target
target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/../include
)
