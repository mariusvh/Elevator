/**
* @file
* @brief Control operations
*/

#ifndef CONTROL_H
#define CONTROL_H


/**
  Tracks which floor the elevator is currently on.
  @param e The elevator that is beeing tracked.
*/
void control_update_floor(elevator_t *e);


/**
  Change direction when we reach top/bottom floor
*/
void control_secure_range();




/**
  Changes motor direction, updates e.dir and e.prevDir.
  @param e The elevator.
  @param dirn New motor/elevator direction.
*/
void control_update_direction(elevator_t *e, elev_motor_direction_t dirn);











#endif
