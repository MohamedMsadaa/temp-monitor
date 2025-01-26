
project(${PROJECT_NAME}-c)

add_executable(${PROJECT_NAME} 
                main.c)

target_link_libraries(${PROJECT_NAME} PRIVATE
                        hal)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/../include)

# Installing the project executable
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
