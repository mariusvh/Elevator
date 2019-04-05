#include "elev.h"
#include <time.h>
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
  STOP,
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
  time_t time;
}elevator_t;



void queue_reset_matrix(elevator_t *e);

void queue_update_matrix(elevator_t *e);

int queue_any_orders(elevator_t *e);

int queue_orders_above(elevator_t *e);

int queue_orders_under(elevator_t *e);

void queue_delete_executed_orders(elevator_t *e);

elev_motor_direction_t queue_choose_direction(elevator_t *e, int value);

int queue_stop_at_floor(elevator_t *e);

/**
  Preparing elevator to start.Initializes elevator attributes.
  @param e The elevator.
*/
void queue_elev_defined_start(elevator_t *e) ;


void queue_print_matix(elevator_t *e);


void queue_update_button_lamps(elevator_t *e);

elev_motor_direction_t queue_floor_inbetween(elevator_t *e);

#endif
