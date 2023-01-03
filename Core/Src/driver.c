/*
 * driver.c
 *
 *  Created on: Nov 30, 2022
 *      Author: PC
 */

#include "driver.h"

GPIO_TypeDef* portOut[6] = {TRAFFIC1_A_GPIO_Port,
						   TRAFFIC1_B_GPIO_Port,
						   TRAFFIC2_A_GPIO_Port,
						   TRAFFIC2_B_GPIO_Port,
						   PLIGHT_R_GPIO_Port,
						   PLIGHT_G_GPIO_Port};

uint16_t pinOut[6] = {TRAFFIC1_A_Pin,
		              TRAFFIC1_B_Pin,
					  TRAFFIC2_A_Pin,
					  TRAFFIC2_B_Pin,
					  PLIGHT_R_Pin,
					  PLIGHT_G_Pin};

GPIO_TypeDef* portIn[4] = {PBUTTON_GPIO_Port,
		                  BUTTON1_GPIO_Port,
						  BUTTON2_GPIO_Port,
						  BUTTON3_GPIO_Port};

uint16_t pinIn[4] = {PBUTTON_Pin,
                     BUTTON1_Pin,
					 BUTTON2_Pin,
					 BUTTON3_Pin};

void writePin(int index, int value)
{
	HAL_GPIO_WritePin(portOut[index], pinOut[index], value);
}

void togglePin(int index)
{
	HAL_GPIO_TogglePin(portOut[index], pinOut[index]);
}

void readPin(int index)
{
	HAL_GPIO_ReadPin(portIn[index], pinIn[index]);
}

void writePWM(TIM_HandleTypeDef* htim3, int value)
{
	__HAL_TIM_SetCompare(htim3, TIM_CHANNEL_1, value);
}


