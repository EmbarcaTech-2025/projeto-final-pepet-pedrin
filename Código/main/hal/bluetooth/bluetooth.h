/*
 * bluetooth.h
 *
 *  Created on: 14 de set. de 2025
 *      Author: peter
 */

#ifndef MAIN_HAL_BLUETOOTH_BLUETOOTH_H_
#define MAIN_HAL_BLUETOOTH_BLUETOOTH_H_

#include <stdint.h>

void BLUETOOTH_Init( const char* );

void BLUETOOTH_SetCallback( void(*cb)( char * , int8_t ) );

#endif /* MAIN_HAL_BLUETOOTH_BLUETOOTH_H_ */
