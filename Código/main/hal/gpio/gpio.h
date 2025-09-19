/*
 * led.h
 *
 *  Created on: 14 de set. de 2025
 *      Author: peter
 */

#ifndef MAIN_HAL_GPIO_GPIO_H_
#define MAIN_HAL_GPIO_GPIO_H_

void GPIO_Init( int pin_led , int pin_buzzer );

void LED_SetON();

void LED_SetOFF();

void BUZZER_SetON();

void BUZZER_SetOFF();


#endif /* MAIN_HAL_GPIO_GPIO_H_ */
