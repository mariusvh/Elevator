/**
* @file
* @brief Timer operations
*/

#ifndef TIMER_H
#define TIMER_H

// Number of seconds the door should be open.
#define DOOR_TIME 3



/**
 * @brief Sets e.time to start time.
 * @param[out] e The elevator.
 */
void timer_start(elevator_t *e);



/**
 * @brief Checks if e.time has increased with DOOR_TIME.
 * @param[in] e The elevator.
 * @return 1 if e.time exceed DOOR_TIME, 0 if not.
 */
int timer_check(elevator_t *e);


#endif
