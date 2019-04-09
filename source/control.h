/**
* @file
* @brief Control operations
*/

#ifndef CONTROL_H
#define CONTROL_H


/**
 * @brief Tracks which floor the elevator e is currently on.
 * @param[in,out] e The elevator that is beeing tracked.
 */
void control_update_floor(elevator_t *e);



/**
 * @brief Changes motor direction of the elevator when it reaches the top/bottom floor.
 */
void control_secure_range();


/**
 * @brief Changes motor direction of the elevator, updates the elevators new direction, e.dir, and its previous direction e.prevDir.
 * @param[in, out] e The elevator.
 * @param[in] dirn The elevators new motor direction.
 */
void control_update_direction(elevator_t *e, elev_motor_direction_t dirn);


/**
  Preparing elevator to start.Initializes elevator attributes.
  @param e The elevator.
*/
void control_elev_defined_start(elevator_t *e) ;



#endif
