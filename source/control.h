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
void control_update_floor(Elevator e);


/**
  Change direction when we reach top/bottom floor
*/
void control_secure_range();





#endif
