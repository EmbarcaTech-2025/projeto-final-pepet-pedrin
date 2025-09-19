/*
 * ar_filter.c
 *
 *  Created on: 14 de set. de 2025
 *      Author: peter
 */

#include "ar_filter.h"

typedef struct {
    TYPE samples[MAX_SAMPLES];
    TYPE mean;
    int16_t sum;
} AR_FILTER_t;

AR_FILTER_t gARFilter;

void AR_FILTER_Init( TYPE value ) 
{
    for( int i = 0; i < MAX_SAMPLES; i++ ) 
    {
        gARFilter.samples[i] = value;
    }
    gARFilter.mean = value;
    gARFilter.sum = value * MAX_SAMPLES;
}

void AR_FILTER_Insert( TYPE sample ) 
{

    gARFilter.sum = gARFilter.sum - gARFilter.samples[MAX_SAMPLES - 1] + sample;

    for ( int i = MAX_SAMPLES - 1 ; i > 0 ; i--) 
    {
        gARFilter.samples[i] = gARFilter.samples[i - 1];
    }

    gARFilter.samples[0] = sample;

    gARFilter.mean = gARFilter.sum / MAX_SAMPLES;
}

TYPE AR_FILTER_GetMean() 
{
    return gARFilter.mean;
}