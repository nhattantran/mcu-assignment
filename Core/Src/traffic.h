/*
 * traffic.h
 *
 *  Created on: Nov 30, 2022
 *      Author: PC
 */

#ifndef SRC_TRAFFIC_H_
#define SRC_TRAFFIC_H_

#define MAX_TIME 50
#define MIN_TIME 2

void pedestrian_fsm(TIM_HandleTypeDef* htim3);
void traffic_fsm_auto();
void main_fsm(TIM_HandleTypeDef* htim3, UART_HandleTypeDef* huart2);
void mode_switch();

#endif /* SRC_TRAFFIC_H_ */
