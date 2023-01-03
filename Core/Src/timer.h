/*
 * timer.h
 *
 *  Created on: Oct 27, 2022
 *      Author: PC
 */

#ifndef SRC_TIMER_H_
#define SRC_TIMER_H_

enum TIMER {TRAFFIC1_TIMER, TRAFFIC2_TIMER, PEDES_TIMEOUT_TIMER, COUNTDOWN_TIMER};
extern enum TIMER timer_type;
int timer_remaining(int index);
void setTimer(int index, int duration);
int timer_timeout(int index);
void timerRun();


#endif /* SRC_TIMER_H_ */
