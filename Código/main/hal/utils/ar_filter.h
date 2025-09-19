/*
 * ar_filter.h
 *
 *  Created on: 14 de set. de 2025
 *      Author: peter
 */

#ifndef MAIN_HAL_UTILS_AR_FILTER_H_
#define MAIN_HAL_UTILS_AR_FILTER_H_

#include <stdint.h>

#define MAX_SAMPLES 5
#define TYPE int8_t


void AR_FILTER_Init( TYPE value );

void AR_FILTER_Insert( TYPE sample );

TYPE AR_FILTER_GetMean();

#endif /* MAIN_HAL_UTILS_AR_FILTER_H_ */
