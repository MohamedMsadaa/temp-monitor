/******************************************************************************
 * File Name:   adc_driver.h
 * Description: This file contains the implementation of adc hardware abstraction 
 *              layer to trigger and read ADC conversion.
 * 
 * 
 * Author:      Mohamed Msadaa
 * Date:        January 25, 2025
 * Version:     1.0.0
 * License:     MIT License
 *
 * Dependencies: Hardware
 *              Doxygen for documentation generation
 *
 *****************************************************************************/

#ifndef ADC_DRIVER_H
#define ADC_DRIVER_H

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief ADC interruption service routine
 * 
 * This function will read value from ADC.
 * 
 * @param none
 * @return void
 */
void HAL_ADC_irq_handler(void) ;

/**
 * @brief callback routine to start ADC conversion
 * 
 * This function trigger ADC to start conversion of sensor.
 * 
 * @param none
 * @return void
 */
void HAL_ADC_start_conversison(void) ;

/**
 * @brief ADC initialization
 * 
 * This function initialize ADC registers and start sampling timer.
 * 
 * @param period uint16_t timer period
 * @return bool true if successful
 */
bool HAL_ADC_init(uint16_t period) ;

/**
 * @brief read ADC sampled value
 * 
 * This function will read ADC sampled value.
 * 
 * @param none
 * @return uint16_t ADC value
 */
uint16_t HAL_ADC_read(void) ;

/**
 * @brief check if new data available
 * 
 * This function will check if new data available
 * just once and reset flag until it is set again.
 * 
 * @param none
 * @return bool if new value available
 */
bool HAL_ADC_is_new_data_available(void) ;

/**
 * @brief ADC Deinit Shutdown
 * 
 * This function will deinit and stop ADC.
 * 
 * @param none
 * @return void
 */
void HAL_ADC_shutdown() ;

#endif /* ADC_DRIVER_H */