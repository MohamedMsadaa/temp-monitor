
project(hal)

add_library(${PROJECT_NAME} STATIC
    ${CMAKE_CURRENT_LIST_DIR}/src/timer_driver.c  ${CMAKE_CURRENT_LIST_DIR}/include/timer_driver.h
    ${CMAKE_CURRENT_LIST_DIR}/src/adc_driver.c  ${CMAKE_CURRENT_LIST_DIR}/include/adc_driver.h
    ${CMAKE_CURRENT_LIST_DIR}/src/eeprom_driver.c  ${CMAKE_CURRENT_LIST_DIR}/include/eeprom_driver.h
    ${CMAKE_CURRENT_LIST_DIR}/src/gpio_driver.c  ${CMAKE_CURRENT_LIST_DIR}/include/gpio_driver.h)


target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include
    #<BUILD_INTERFACE>
)
