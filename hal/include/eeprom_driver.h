/******************************************************************************
 * File Name:   eeprom_driver.h
 * Description: This file contains the implementation of hardware abstraction 
 *              layer to read from EEPROM.
 * 
 * 
 * Author:      Mohamed Msadaa
 * Date:        January 25, 2025
 * Version:     1.0.0
 * License:     MIT License
 *
 * Dependencies: Hardware??
 *              Doxygen for documentation generation
 *
 *****************************************************************************/

#ifndef EEPROM_DRIVER_H
#define EEPROM_DRIVER_H

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief EEPROM init function
 * 
 * This function will init EEPROM.
 * 
 * @param none might require paraneters
 * @return bool true if successful
 */
bool HAL_eeprom_init() ;

/**
 * @brief EEPROM read function
 * 
 * This function will read value from EEPROM.
 * 
 * @param address uint32_t address of eeprom to read from
 * @param address uint32_t * pointer of value
 * @return bool true if successful
 */
bool HAL_eeprom_read(uint32_t address, uint32_t *value) ;

/**
 * @brief EEPROM read function
 * 
 * This function will read value in string form from EEPROM.
 * 
 * @param address uint32_t address of eeprom to read from
 * @param address char * pointer of char array
 * @return bool true if successful
 */
bool HAL_eeprom_read_string(uint32_t address, char *value, uint32_t size);

#endif /* EEPROM_DRIVER */
