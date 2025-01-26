#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "interruption.h"
#include "timer_driver.h"
#include "adc_driver.h"

/******************************************************************************
 *                  MOCK HARDWARE REGISTER DEFINITIONS SECTION
 *****************************************************************************/
#define ADC_START_CONVERSION()   (printf("Mock: Start ADC Conversion\n"))   // Start ADC Conversion
#define ADC_RESULT_REGISTER      (90)  // Mock ADC data register
#define ADC_ISR_FLAG             (true)   // ADC Interrupt Status
#define ADC_INIT()               (printf("Mock: INIT ADC \n"))   // Init ADC
#define ADC_STOP()               (printf("Mock: STOP ADC \n"))   // Stop ADC
#define ADC_DEINIT()             (printf("Mock: DEINIT ADC \n"))   // Deinit ADC 
#define ADC_ENABLE_INTERRUPT()   (printf("Mock: Enable ADC interrupt\n"))   // Enable ADC interrupt
#define ADC_CLEAR_INTERRUPT()    (printf("Mock: Clear ADC interrupt\n"))   // Clear ADC interrupt
#define ADC_BUSY                 (false)  

/******************************************************************************
 *                    GLOBAL VARIABLES DEFINITIONS SECTION
 *****************************************************************************/

volatile uint16_t g_adc_value = 0;  // Store ADC result
volatile bool g_adc_is_new_value_available = false;
static bool g_is_ADC_init = false;

/******************************************************************************
 *                    PUBLIC FUNCTIONS DEFINITIONS SECTION
 *****************************************************************************/

/**
 * @brief ADC interruption service routine
 * 
 * This function will read value from ADC.
 * 
 * @param none
 * @return void
 */
void HAL_ADC_irq_handler(void) {
    if (ADC_ISR_FLAG) {
        g_adc_value = ADC_RESULT_REGISTER;  // Read ADC result
        g_adc_is_new_value_available = true;
        // Clear ADC interrupt flag (mock)
        ADC_CLEAR_INTERRUPT();
    }
}

/**
 * @brief callback routine to start ADC conversion
 * 
 * This function trigger ADC to start conversion of sensor.
 * 
 * @param none
 * @return void
 */
void HAL_ADC_start_conversison(void) {
    
    if (!g_is_ADC_init) {
        return;
    }

    /* if ADC is busy maybe wait or stop it (needs to be tested) */
    if (ADC_BUSY) {
        //ADC_STOP();
        return;
    }
    
    ADC_START_CONVERSION();
}

/**
 * @brief ADC initialization
 * 
 * This function initialize ADC registers and start sampling timer.
 * 
 * @param period uint16_t timer period
 * @return bool true if successful
 */
bool HAL_ADC_init(uint16_t period) {
    /* Protect against concurrent access */
    __disable_irq();

    /* Make sure ADC is stopped and deintialize it before attempting to init again */
    ADC_STOP();
    ADC_DEINIT();

    /* Init / Configure ADC */
    ADC_INIT();
    g_is_ADC_init = true;
    ADC_ENABLE_INTERRUPT();  // Enable ADC interrupt
    
    /* Initialize Timer and start it */
    HAL_timer_init(period, HAL_ADC_start_conversison, true);
    HAL_timer_start();

    __enable_irq();

    return true;
}

/**
 * @brief read ADC sampled value
 * 
 * This function will read ADC sampled value.
 * 
 * @param none
 * @return uint16_t ADC value
 */
uint16_t HAL_ADC_read(void) {
    /* Protect against concurrent access */
    __disable_irq();
    uint16_t value = g_adc_value;
    __enable_irq();
    return value;
}

/**
 * @brief check if new data available
 * 
 * This function will check if new data available
 * just once and reset flag until it is set again.
 * 
 * @param none
 * @return bool if new value available
 */
bool HAL_ADC_is_new_data_available(void) {
    /* Protect against concurrent access */
    __disable_irq();
    bool value = g_adc_is_new_value_available;
    /* Reset value */
    g_adc_is_new_value_available = false;
    __enable_irq();
    return value;
}

/**
 * @brief ADC Deinit Shutdown
 * 
 * This function will deinit and stop ADC.
 * 
 * @param none
 * @return void
 */
void HAL_ADC_shutdown() {
    /* Protect against concurrent access */
    __disable_irq();

    HAL_timer_stop();
    
    /* Make sure ADC is stopped and deintialized before attempting to init again */
    ADC_STOP();
    ADC_DEINIT();

    __enable_irq();
}
