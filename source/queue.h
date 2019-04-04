#include "elev.h"

/**
* @file
* @brief Queue operations
*/

#ifndef QUEUE_H
#define QUEUE_H


/**
  Different states
*/
typedef enum states {
  IDLE,
  MOVE,
  ESTOP,
  DOOR_OPEN
} state_t;


/**
  The elevator
*/
typedef struct elevator{
  elev_motor_direction_t dir;
  elev_motor_direction_t prevDir;
  int floor;
  state_t state;
  int queue[N_FLOORS][N_BUTTONS];
}elevator_t;



void queue_reset_matrix(elevator_t *e);

void queue_update_matrix(elevator_t *e);

int queue_any_orders(elevator_t *e);

int queue_orders_above(elevator_t *e);

int queue_orders_under(elevator_t *e);

void queue_delete_executed_orders(elevator_t *e);

elev_motor_direction_t queue_choose_direction(elevator_t *e);

int queue_stop_at_floor(elevator_t *e);

/**
  Preparing elevator to start.Initializes elevator attributes.
  @param e The elevator.
*/
void elev_defined_start(elevator_t *e);



#endif
