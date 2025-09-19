#include "hal/bluetooth/bluetooth.h"
#include "hal/utils/ar_filter.h"
#include "hal/gpio/gpio.h"
#include <stdio.h>
#include <string.h>
#include <freertos/FreeRTOS.h>

/****************************************
*				Defines
*****************************************/
#define LED_OUTPUT 2
#define BUZZER_OUTPUT 4

/****************************************
*				Type Definitions
*****************************************/
typedef struct{
	const char* device_name;
	const char* phone_name;
	float distance;
	float max_distance;
	bool hasNewMessage;
	bool isInitialized;
	int timer;
}AIRLEASH_t;

/****************************************
*				Global Variables
*****************************************/
AIRLEASH_t gAirLeash = {
	.device_name = "AIR_LEASH",
	.phone_name = "POCO C65",
	.distance = 0,
	.max_distance = 150.0f,
	.hasNewMessage = false,
	.isInitialized = false,
	.timer = 5
};

/****************************************
*				Helper Functions
*****************************************/
float DecibelsToDistance( int8_t decibels )
{
	float distance;
	distance = -5*decibels - 118.75;
	return distance;
}

void process_data( char* name, int8_t rssi ) 
{
    if( strcmp( name, gAirLeash.phone_name ) == 0 ) 
    {
		if( !gAirLeash.isInitialized )
		{
			gAirLeash.isInitialized = true;
			printf("Connection Initialized\n");
		}
		gAirLeash.hasNewMessage = true;
        AR_FILTER_Insert( rssi );
        //printf("%d %f\n",rssi, DecibelsToDistance( AR_FILTER_GetMean() ));
    }
}

/****************************************
*				Tasks
*****************************************/
void TASK_Application( void* param ) 
{
    while( true ) 
    {
		printf("Timer: %d\n", gAirLeash.timer );
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        
        if( gAirLeash.isInitialized )
        {
			if( gAirLeash.hasNewMessage )
			{
				gAirLeash.timer = 5;	//Reset communication timeout
				if( DecibelsToDistance( AR_FILTER_GetMean() ) < gAirLeash.max_distance )
				{
					BUZZER_SetOFF();
				}
				else 
				{
					BUZZER_SetON();
				}
				gAirLeash.hasNewMessage = false;
			}
			else 
			{
				if( gAirLeash.timer )
				{
					BUZZER_SetOFF();
					gAirLeash.timer--;
				}
				else 
				{
					BUZZER_SetON();
				}
			}
		}
		else 
		{
			BUZZER_SetOFF();
		}
    }
}

void TASK_LED( void* param ) 
{
    while( true )
    {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        
        if( gAirLeash.isInitialized )
        {
			LED_SetON();
		}
		else
		{
			LED_SetOFF();
		}
    }
}
/****************************************
*				Application
*****************************************/
void app_main(void)
{
    BLUETOOTH_SetCallback( process_data );
    AR_FILTER_Init(0);
    GPIO_Init( LED_OUTPUT , BUZZER_OUTPUT );
     
    xTaskCreate(TASK_Application, "task", 2048, NULL, 5, NULL);
    xTaskCreate(TASK_LED, "task", 2048, NULL, 5, NULL);
    
    BLUETOOTH_Init( gAirLeash.device_name );
}