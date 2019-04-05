/**
* @file
* @brief Timer operations
*/

#ifndef TIMER_H
#define TIMER_H

// Number of seconds the door should be open.
#define DOOR_TIME 3

void timer_start(elevator_t *e);

int timer_check(elevator_t *e);


#endif
