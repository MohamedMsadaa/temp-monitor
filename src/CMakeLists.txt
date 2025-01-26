
project(${PROJECT_NAME}-c)

add_executable(${PROJECT_NAME} 
                ${CMAKE_CURRENT_LIST_DIR}/main.c
                ${CMAKE_CURRENT_LIST_DIR}/led_controller.c ${CMAKE_CURRENT_LIST_DIR}/../include/led_controller.h
                ${CMAKE_CURRENT_LIST_DIR}/temp_manager.c ${CMAKE_CURRENT_LIST_DIR}/../include/temp_manager.h)

target_link_libraries(${PROJECT_NAME} PRIVATE
                        hal)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/../include)

# Installing the project executable
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
