/*
 * traffic.c
 *
 *  Created on: Nov 30, 2022
 *      Author: PC
 */
/* NOTES */
//PLIGHT will turn on when PBUTTON is pressed
//Timeout for PLIGHT can be freely defined
//When will PBUZZER active is freely defined

#include "button.h"
#include "timer.h"
#include "traffic.h"
#include "driver.h"

enum TRAFFIC_FSM_MODE {TRAFFIC_FSM_INIT, AUTOMATIC, MANUAL, TUNING};
enum TRAFFIC_FSM_MODE trafficFsmMode = TRAFFIC_FSM_INIT;

enum TRAFFIC_MODE {TRAFFIC_INIT, RED, GREEN, YELLOW};
enum TRAFFIC_MODE traffic1Mode = TRAFFIC_INIT;
enum TRAFFIC_MODE traffic2Mode = TRAFFIC_INIT;

enum TUNING_MODE {TUNE_INIT, TUNE_RED, TUNE_GREEN, TUNE_YELLOW};

enum PEDES_MODE {PEDES_RUN, PEDES_STOP};
enum PEDES_MODE pedesMode = PEDES_STOP;

int led_red_time = 5;
int led_green_time = 3;
int led_yellow_time = 2;
int tuning_mode = TUNE_INIT;
char writeStr[10];

void traffic_fsm_auto()
{
	//-------------------------------------------------
	switch (traffic1Mode)
	{
	case TRAFFIC_INIT:
			//Initialze necessary variables
			//TODO
			setTimer(TRAFFIC1_TIMER, led_green_time * 1000);
			traffic1Mode = GREEN;
			writePin(TRAFFIC1_A, 0);
			writePin(TRAFFIC1_B, 1);
			break;
	case RED:
		//Implement case RED manual
		//If timeout, switch to AUTO mode
		//TODO
		if (timer_timeout(TRAFFIC1_TIMER))
		{
			setTimer(TRAFFIC1_TIMER, led_green_time * 1000);
			traffic1Mode = GREEN;
			writePin(TRAFFIC1_A, 0);
			writePin(TRAFFIC1_B, 1);
		}
		break;
	case YELLOW:
		//Implement case YELLOW manual
		//If timeout, switch to AUTO mode
		//TODO
		if (timer_timeout(TRAFFIC1_TIMER))
		{
			setTimer(TRAFFIC1_TIMER, led_red_time * 1000);
			traffic1Mode = RED;
			writePin(TRAFFIC1_A, 1);
			writePin(TRAFFIC1_B, 0);
		}
		break;
	case GREEN:
		//Implement case GREEN manual
		//If timeout, switch to AUTO mode
		//TODO
		if (timer_timeout(TRAFFIC1_TIMER))
		{
			setTimer(TRAFFIC1_TIMER, led_yellow_time * 1000);
			traffic1Mode = YELLOW;
			writePin(TRAFFIC1_A, 1);
			writePin(TRAFFIC1_B, 1);
		}
		break;
	default:
		break;
	}
	//-------------------------------------------------
	switch (traffic2Mode)
	{
	case TRAFFIC_INIT:
		//Initialze necessary variables
		//TODO
		setTimer(TRAFFIC2_TIMER, led_red_time * 1000);
		traffic2Mode = RED;
		writePin(TRAFFIC2_A, 1);
		writePin(TRAFFIC2_B, 0);
		break;
	case RED:
		//Implement case RED manual
		//If timeout, switch to AUTO mode
		//TODO
		if (timer_timeout(TRAFFIC2_TIMER))
		{
			setTimer(TRAFFIC2_TIMER, led_green_time * 1000);
			traffic2Mode = GREEN;
			writePin(TRAFFIC2_A, 0);
			writePin(TRAFFIC2_B, 1);
		}
		break;
	case YELLOW:
		//Implement case YELLOW manual
		//If timeout, switch to AUTO mode
		//TODO
		if (timer_timeout(TRAFFIC2_TIMER))
		{
			setTimer(TRAFFIC2_TIMER, led_red_time * 1000);
			traffic2Mode = RED;
			writePin(TRAFFIC2_A, 1);
			writePin(TRAFFIC2_B, 0);
		}
		break;
	case GREEN:
		//Implement case GREEN manual
		//If timeout, switch to AUTO mode
		//TODO
		if (timer_timeout(TRAFFIC2_TIMER))
		{
			setTimer(TRAFFIC2_TIMER, led_yellow_time * 1000);
			traffic2Mode = YELLOW;
			writePin(TRAFFIC2_A, 1);
			writePin(TRAFFIC2_B, 1);
		}
		break;
	default:
		break;
	}
	//-------------------------------------------------
}

void traffic_fsm_manual()
{
	//-------------------------------------------------
	if (isButtonPressed(BUTTON_2))
	{
		switch (traffic1Mode)
		{
		case TRAFFIC_INIT:
			//Initialze necessary variables
			//TODO
			traffic1Mode = GREEN;
			writePin(TRAFFIC1_A, 0);
			writePin(TRAFFIC1_B, 1);
			break;
		case RED:
			//Implement case RED manual
			//If timeout, switch to AUTO mode
			//TODO
				traffic1Mode = GREEN;
				writePin(TRAFFIC1_A, 0);
				writePin(TRAFFIC1_B, 1);
			break;
		case YELLOW:
			//Implement case YELLOW manual
			//If timeout, switch to AUTO mode
			//TODO
				traffic1Mode = RED;
				writePin(TRAFFIC1_A, 1);
				writePin(TRAFFIC1_B, 0);
			break;
		case GREEN:
			//Implement case GREEN manual
			//If timeout, switch to AUTO mode
			//TODO
				traffic1Mode = YELLOW;
				writePin(TRAFFIC1_A, 1);
				writePin(TRAFFIC1_B, 1);
			break;
		default:
			break;
		}
		//-------------------------------------------------
		switch (traffic2Mode)
		{
		case TRAFFIC_INIT:
			//Initialze necessary variables
			//TODO
			traffic2Mode = RED;
			writePin(TRAFFIC2_A, 1);
			writePin(TRAFFIC2_B, 0);
			break;
		case RED:
			//Implement case RED manual
			//If timeout, switch to AUTO mode
			//TODO
				traffic2Mode = GREEN;
				writePin(TRAFFIC2_A, 0);
				writePin(TRAFFIC2_B, 1);
			break;
		case YELLOW:
			//Implement case YELLOW manual
			//If timeout, switch to AUTO mode
			//TODO
				traffic2Mode = RED;
				writePin(TRAFFIC2_A, 1);
				writePin(TRAFFIC2_B, 0);
			break;
		case GREEN:
			//Implement case GREEN manual
			//If timeout, switch to AUTO mode
			//TODO
				traffic2Mode = YELLOW;
				writePin(TRAFFIC2_A, 1);
				writePin(TRAFFIC2_B, 1);
			break;
		default:
			break;
		}
	}
	//-------------------------------------------------
}
/*
 * tuning FSM
 * BUTTON1 to switch mode
 * BUTTOn2 to switch LED to adjust
 * BUTTON3 to increase, if time > MAX_TIME then rollback to MIN_TIME
 * PES_BUTTON to save and switch to auto mode
 * BUTTON(N) -> isButtonPresed(N-1)
 * */

void tuning_fsm(){
	switch(tuning_mode){
	//tune the green led
		case TUNE_GREEN:
			if(isButtonPressed(BUTTON_2)) tuning_mode = TUNE_YELLOW;
			else
			{
				writePin(TRAFFIC1_A, 0);
				writePin(TRAFFIC1_B, 1);
				writePin(TRAFFIC2_A, 0);
				writePin(TRAFFIC2_B, 1);
				if(isButtonPressed(BUTTON_3)){
					led_green_time++;
					if(led_green_time > MAX_TIME) led_green_time = MIN_TIME;
				}
			}
			break;
		//tune the yellow led
		case TUNE_YELLOW:
			if(isButtonPressed(BUTTON_2)) tuning_mode = TUNE_GREEN;
			else
			{
				writePin(TRAFFIC1_A, 1);
				writePin(TRAFFIC1_B, 1);
				writePin(TRAFFIC2_A, 1);
				writePin(TRAFFIC2_B, 1);
				if(isButtonPressed(BUTTON_3)){
					led_yellow_time++;
					if(led_yellow_time > MAX_TIME) led_yellow_time = MIN_TIME;
				}
			}
			break;
	}
}

void pedestrian_fsm(TIM_HandleTypeDef* htim3)
{
	switch (pedesMode)
	{
	case PEDES_RUN:
		if (timer_timeout(PEDES_TIMEOUT_TIMER))
		{
			pedesMode = PEDES_STOP;
		}
		if (isButtonPressed(P_BUTTON))
		{
			setTimer(PEDES_TIMEOUT_TIMER, (led_red_time + led_green_time + led_yellow_time) * 1000);
		}
		switch (traffic2Mode)
		{
		case TRAFFIC_INIT:
			writePin(PLIGHT_R, 1);
			writePin(PLIGHT_G, 0);
			writePWM(htim3, 0);
			break;
		case RED:
			writePin(PLIGHT_R, 1);
			writePin(PLIGHT_G, 0);
			writePWM(htim3, 0);
			break;
		case GREEN:
			writePin(PLIGHT_R, 0);
			writePin(PLIGHT_G, 1);
			writePWM(htim3, 0);
			break;
		case YELLOW:
			writePin(PLIGHT_R, 1);
			writePin(PLIGHT_G, 1);
			writePWM(htim3, 10);
			break;
		default:
			break;
		}
		break;
	case PEDES_STOP:
		if (isButtonPressed(P_BUTTON))
		{
			pedesMode = PEDES_RUN;
			setTimer(PEDES_TIMEOUT_TIMER, (led_red_time + led_green_time + led_yellow_time) * 1000);
		}
		else
		{
			writePin(PLIGHT_R, 0);
			writePin(PLIGHT_G, 0);
			writePWM(htim3, 0);
		}
		break;
	}
}
/*
 * Mode switch function
 * switch to appopriate function
 */

void main_fsm(TIM_HandleTypeDef* htim3, UART_HandleTypeDef* huart2)
{
	switch (trafficFsmMode)
	{
	case TRAFFIC_FSM_INIT:
		//Initialize necessary variables
		//TODO
		trafficFsmMode = AUTOMATIC;
		writePin(TRAFFIC1_A, 0);
		writePin(TRAFFIC1_B, 0);
		writePin(TRAFFIC2_A, 0);
		writePin(TRAFFIC2_B, 0);
		writePin(PLIGHT_R, 0);
		writePin(PLIGHT_G, 0);
		setTimer(COUNTDOWN_TIMER, 10);
		break;
	case AUTOMATIC:
		//Default mode
		//Typical auto traffic light
		//Implement the function below
		//TODO
		if (isButtonPressed(BUTTON_1))
		{
			trafficFsmMode = MANUAL;
		}
		else
		{
			pedestrian_fsm(htim3);
			traffic_fsm_auto();
		}
		if (timer_timeout(COUNTDOWN_TIMER))
		{
			HAL_UART_Transmit(huart2, writeStr, sprintf(writeStr, "!LED7SEG:%d#\r\n", timer_remaining(PEDES_TIMEOUT_TIMER)), 1000);
			//HAL_UART_Transmit(huart2, writeStr, sprintf(writeStr, "!2:%d#\r\n", timer_remaining(TRAFFIC2_TIMER)), 1000);
			setTimer(COUNTDOWN_TIMER, 1000);
		}
		break;
	case MANUAL:
		//Pressing BUTTON1 while in AUTOMATIC mode will switch to MANUAL mode
		//In MANUAL mode, BUTTON2 will manually switch to another state of traffic light
		//BUTTON3 will switch to the previous state of the traffic light
		//Implement the function below
		if (isButtonPressed(BUTTON_1))
		{
			trafficFsmMode = TUNING;
			tuning_mode = TUNE_GREEN;
			pedesMode = PEDES_STOP;
		}
		else
		{
			//pedestrian_fsm(htim3);
			traffic_fsm_manual();
		}
		break;
	case TUNING:
		//Pressing BUTTON1 in MANUAL mode will switch to TUNING mode
		//In TUNING mode, BUTTON2 will choose the LED we want to tune
		//BUTTON3 will increase the duration by 1 per press, by 10 per long press
		//Implement TUNING mode
		//TODO
		//pedesMode = PEDES_STOP;
		if (isButtonPressed(BUTTON_1))
		{
			led_red_time = led_yellow_time + led_green_time;
			trafficFsmMode = AUTOMATIC;
		}
		else
		{
			//pedesMode = PEDES_STOP;
			//pedestrian_fsm(htim3);
			tuning_fsm();
		}
		break;
	default:
		break;
	}
}


