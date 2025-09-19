/*
 * led.c
 *
 *  Created on: 14 de set. de 2025
 *      Author: peter
 */

#include <driver/gpio.h>
#include "gpio.h"

typedef struct
{
	int pin_led;
	int pin_buzzer;
}GPIO_t;

GPIO_t gGpio;

void GPIO_Init( int pin_led , int pin_buzzer )
{
	gGpio.pin_led = pin_led;
	gGpio.pin_buzzer = pin_buzzer;
	
	gpio_config_t gpio_cfg = {
	    .pin_bit_mask = (1ULL << gGpio.pin_led)|(1ULL << gGpio.pin_buzzer),
	    .mode = GPIO_MODE_OUTPUT,
	    .pull_up_en = GPIO_PULLUP_DISABLE,
	    .pull_down_en = GPIO_PULLDOWN_DISABLE,
	    .intr_type = GPIO_INTR_DISABLE
	};
	gpio_config( &gpio_cfg );
}

void LED_SetON()
{
	gpio_set_level(gGpio.pin_led, 1);
}

void LED_SetOFF()
{
	gpio_set_level(gGpio.pin_led, 0);
}

void BUZZER_SetON()
{
	gpio_set_level(gGpio.pin_buzzer, 1);
}

void BUZZER_SetOFF()
{
	gpio_set_level(gGpio.pin_buzzer, 0);
}