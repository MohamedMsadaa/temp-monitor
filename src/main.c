/**
 * @file main.c
 * @brief Temperature Monitoring and Visualization System
 *
 * This file contains the main entry point as bare metal OS for the temperature monitoring system.
 * The system reads temperature values from an ADC, processes them, and controls
 * LED indicators based on predefined temperature thresholds.
 *
 * @author Mohamed Msadaa
 * @date 26.01.2025
 * @version 1.0
 *
 * @note This project is designed for demo purposes with mocked hardware.
 */

#include <stdio.h>

#include "eeprom_config.h"
#include "eeprom_driver.h"
#include "os.h"

#include "led_controller.h"
#include "temp_manager.h"

int main() {
    /* Initialize system */
    if(!led_controller_init()) {
        printf("Error Initializing led controller\n");
    }

    if(!temp_manager_init()) {
        printf("Error Initializing temp manager\n");
    }

   /* Synchronize : Wait for first temperature reading
        This will minimize jitter  */
    while (!temp_manager_is_new_data_available()) { };
    
    /* Bare metal OS loop */
    while (true) {
        /* Get current time in us */
        uint32_t start_time = get_time_us();
        temp_status_t status = temp_manager_read_status();
        bool result = true;

        switch (status)
        {
            case TEMP_STATUS_CRITICAL:
                result &= led_controller_set_state(LED_GREEN_ID, LED_STATE_OFF);
                result &= led_controller_set_state(LED_YELLOW_ID, LED_STATE_OFF);
                result &= led_controller_set_state(LED_RED_ID, LED_STATE_ON);
                break;

            case TEMP_STATUS_WARNING:
                result &= led_controller_set_state(LED_GREEN_ID, LED_STATE_OFF);
                result &= led_controller_set_state(LED_YELLOW_ID, LED_STATE_ON);
                result &= led_controller_set_state(LED_RED_ID, LED_STATE_OFF);
                break;

            case TEMP_STATUS_NORMAL:
                result &= led_controller_set_state(LED_GREEN_ID, LED_STATE_ON);
                result &= led_controller_set_state(LED_YELLOW_ID, LED_STATE_OFF);
                result &= led_controller_set_state(LED_RED_ID, LED_STATE_OFF);
                break;
            
            default: /* Temperature reading failure set all LED ON */
                result &= led_controller_set_state(LED_GREEN_ID, LED_STATE_ON);
                result &= led_controller_set_state(LED_YELLOW_ID, LED_STATE_ON);
                result &= led_controller_set_state(LED_RED_ID, LED_STATE_ON);
                printf("Error reading temp \n");
                break;
        }
        if (!result) {
            printf("Error controlling LED \n");
        }

        /* Other functionality */

        /* Compute execution time */
        uint32_t elapsed_time_us = get_time_us() - start_time;
        uint32_t sleep_time = CFG_TEMP_SAMPLING_PERIOD_US - elapsed_time_us;

        /* Sleep for the remaining time */
        sleep(sleep_time);

        /* Synchronize : Wait for next temperature reading
            This will minimize jitter  */
        while (!temp_manager_is_new_data_available()) { };
    }
    
    return 0;
}