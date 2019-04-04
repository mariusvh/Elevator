
#include "queue.h"
#include "elev.h"
#include "io.h"
#include <stdio.h>

void queue_reset_matrix(elevator_t *e){
  for (int i = 0; i < N_FLOORS; i++) {
    for (int j = 0; j < N_BUTTONS; j++) {
      e->queue[i][j] = 0;
    }
  }
  e->queue[0][1] = -1;
  e->queue[N_FLOORS][0] = -1;
}

void queue_update_matrix(elevator_t *e){
  for (int i = 0; i < N_FLOORS; i++) {
    for (int j = 0; j < N_BUTTONS; j++) {
      e->queue[i][j] = e->queue[i][j] || elev_get_button_signal(j,i); // j is elev_button_type   BUTTON_CALL_UP = 0, BUTTON_CALL_DOWN = 1, BUTTON_COMMAND = 2
    }
  }
  e->queue[0][1] = -1;
  e->queue[N_FLOORS][0] = -1;
}


int queue_any_orders(elevator_t *e){
  for (int i = 0; i < N_FLOORS; i++) {
    for (int j = 0; j < N_BUTTONS; j++) {
      if (e->queue[i][j] == 1) {
        return 1;
      }
    }
  }
  return 0;
}



int queue_orders_above(elevator_t *e){
  for (int i = e->floor + 1; i < N_FLOORS; i++) {
    for (int j = 0; j < N_BUTTONS; j++) {
      if (e->queue[i][j] == 1) {
        return 1;
      }
    }
  }
  return 0;
}

int queue_orders_under(elevator_t *e){
  for (int i = 0; i < e->floor; i++) {
    for (int j = 0; j < N_BUTTONS; j++) {
      if (e->queue[i][j] == 1) {
        return 1;
      }
    }
  }
  return 0;
}

void queue_delete_executed_orders(elevator_t *e){
  for (int i = 0; i < N_BUTTONS; i++) {
    e->queue[e->floor][i] = 0;
  }
  e->queue[0][1] = -1;
  e->queue[N_FLOORS][0] = -1;
}

elev_motor_direction_t queue_choose_direction(elevator_t *e){
  switch (e->prevDir) {
    case DIRN_UP:
      if (queue_orders_above(e)) {
        return DIRN_UP;
     }
      if (queue_orders_under(e)) {

        return DIRN_DOWN;
      }
      return DIRN_STOP;

    case DIRN_DOWN:
      if (queue_orders_under(e)) {
        return DIRN_DOWN;
      }
      if (queue_orders_above(e)) {
        return DIRN_UP;
      }
      return DIRN_STOP;


    case DIRN_STOP:
      if (queue_orders_under(e)) {
        return DIRN_DOWN;
      }
      if (queue_orders_above(e)) {
        return DIRN_UP;
      }
      return DIRN_STOP;

    default:
      return DIRN_STOP;
  }

}

int queue_stop_at_floor(elevator_t *e) {
  switch (e->dir) {
    case DIRN_UP:
      if (e->queue[e->floor][BUTTON_CALL_UP] || e->queue[e->floor][BUTTON_COMMAND] || !queue_orders_above(e)) {
        return 1;
      }
      return 0;

    case DIRN_DOWN:
    if (e->queue[e->floor][BUTTON_CALL_DOWN] || e->queue[e->floor][BUTTON_COMMAND] || !queue_orders_under(e)) {
        return 1;
      }
      return 0;

    default:
      return 1;
  }
}


void elev_defined_start(elevator_t *e) {
    e->floor = elev_get_floor_sensor_signal();
    if (e->floor != -1) {
        elev_set_floor_indicator(e->floor);
        e->dir = DIRN_STOP;
        e->prevDir = DIRN_STOP;
        e->state = IDLE;
        queue_reset_matrix(e);
    }
    else {
        elev_set_motor_direction(DIRN_DOWN);
        while (elev_get_floor_sensor_signal() == -1) {
        }
        elev_set_motor_direction(DIRN_STOP);
        e->floor = elev_get_floor_sensor_signal();
        elev_set_floor_indicator(e->floor);
        e->dir = DIRN_STOP;
        e->prevDir = DIRN_STOP;
        e->state = IDLE;
        queue_reset_matrix(e);
    }
}
