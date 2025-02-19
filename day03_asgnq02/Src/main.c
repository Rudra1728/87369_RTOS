/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>
#include <stdio.h>
#include "led.h"
#include"FreeRTOSConfig.h"
#include"FreeRTOS.h"
#include"task.h"
#include "uart.h"


#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

typedef struct {
	uint32_t led;
	uint32_t rate;
}task_t;

task_t t1, t2, t3, t4;


void vLedTask(void *pvParam){
	task_t *ledParams = (task_t *)pvParam;

	while(1){

		led_toggle(ledParams->led);
		vTaskDelay(ledParams->rate / portTICK_RATE_MS);
	}

	vTaskDelete(NULL);
}

int main(void){


	t1.led = LED_RED;
	t1.rate = 1000;

	t2.led = LED_BLUE;
	t2.rate = 2000;

	t3.led = LED_ORANGE;
	t3.rate = 3000;

	t4.led = LED_GREEN;
	t4.rate = 4000;

	led_init(t1.led);
	led_init(t2.led);
	led_init(t3.led);
	led_init(t4.led);

	xTaskCreate(vLedTask, "Aperiodic1", configMINIMAL_STACK_SIZE, (void*)&t1, 4, NULL);
	xTaskCreate(vLedTask, "Aperiodic2", configMINIMAL_STACK_SIZE, (void*)&t2, 3, NULL);
	xTaskCreate(vLedTask, "Aperiodic3", configMINIMAL_STACK_SIZE, (void*)&t3, 2, NULL);
	xTaskCreate(vLedTask, "Aperiodic4", configMINIMAL_STACK_SIZE, (void*)&t4, 1, NULL);

	vTaskStartScheduler();
	while(1);

	return 0;

}














