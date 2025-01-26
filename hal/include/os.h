/******************************************************************************
 * File Name:   os.h
 * Description: This file contains some os functions.
 * 
 * 
 * Author:      Mohamed Msadaa
 * Date:        January 26, 2025
 * Version:     1.0.0
 * License:     MIT License
 *
 * Dependencies: Hardware
 *              Doxygen for documentation generation
 *
 *****************************************************************************/
    
    
#ifndef OS_H
#define OS_H

#define sleep(time_us)  ((void)0)  // Mock the sleep function
#define get_time_us()   (1)  // Mock the time function

#endif /* OS_H */