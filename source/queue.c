#include "queue.h"
#include "elev.h"
#include <stdio.h>

void queue_reset_matrix(elevator_t *e){
  for (int i = 0; i < N_FLOORS; i++) {
    for (int j = 0; j < N_BUTTONS; j++) {
      e->queue[i][j] = 0;
    }
  }
  e->queue[0][1] = -1;
  e->queue[N_FLOORS-1][0] = -1;
}

void queue_update_matrix(elevator_t *e){
  for (int i = 0; i < N_FLOORS-1; i++) {
      e->queue[i][BUTTON_CALL_UP] = e->queue[i][BUTTON_CALL_UP] || elev_get_button_signal(BUTTON_CALL_UP,i);
  }
  for (int j = 1;j < N_FLOORS ;j++) {
      e->queue[j][BUTTON_CALL_DOWN] = e->queue[j][BUTTON_CALL_DOWN] || elev_get_button_signal(BUTTON_CALL_DOWN,j);
  }
  for (int k = 0; k < N_FLOORS; k++) {
      e->queue[k][BUTTON_COMMAND] = e->queue[k][BUTTON_COMMAND] || elev_get_button_signal(BUTTON_COMMAND,k);
  }
  e->queue[0][1] = -1;
  e->queue[N_FLOORS-1][0] = -1;
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
  e->queue[N_FLOORS-1][0] = -1;
}



int queue_stop_at_floor(elevator_t *e) {
  switch (e->dir) {
    case DIRN_UP:
      if ((e->queue[e->floor][BUTTON_CALL_UP] || e->queue[e->floor][BUTTON_COMMAND] || !queue_orders_above(e)) && elev_get_floor_sensor_signal() != -1) {
        return 1;
      }
      return 0;

    case DIRN_DOWN:
        if ((e->queue[e->floor][BUTTON_CALL_DOWN] || e->queue[e->floor][BUTTON_COMMAND] || !queue_orders_under(e)) && elev_get_floor_sensor_signal() != -1) {
            return 1;
        }
        return 0;

    case DIRN_STOP:
        if (e->floor == 0 && elev_get_floor_sensor_signal() != -1) {
            if (e->queue[e->floor][BUTTON_CALL_UP] || e->queue[e->floor][BUTTON_COMMAND]) {
                return 1;
            }
            return 0;
        }
        if (e->floor == N_FLOORS-1 && elev_get_floor_sensor_signal() != -1) {
            if (e->queue[e->floor][BUTTON_CALL_DOWN] || e->queue[e->floor][BUTTON_COMMAND]) {
                return 1;
            }
            return 0;
        }
        if (e->floor != -1 && elev_get_floor_sensor_signal() != -1) {
            if (e->queue[e->floor][BUTTON_CALL_DOWN]|| e->queue[e->floor][BUTTON_CALL_UP] || e->queue[e->floor][BUTTON_COMMAND]) {
                return 1;
            }
            return 0;
        }
    }
    return 0;
}


elev_motor_direction_t queue_choose_direction(elevator_t *e, int value){
    if (value == -1) {
        return queue_floor_inbetween(e);
      }
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


void queue_print_matix(elevator_t *e){
    for (int i = 0; i < N_FLOORS; i++) {
        for (size_t j = 0; j < N_BUTTONS; j++) {
            printf("%d\t",e->queue[i][j]);
        }
        printf("\n");
    }
}


void queue_update_button_lamps(elevator_t *e) {
    for (int i = 0; i < N_FLOORS-1; i++) {
        if (e->queue[i][BUTTON_CALL_UP] == 1) {
            elev_set_button_lamp(BUTTON_CALL_UP,i,1);
        }
        else {
            elev_set_button_lamp(BUTTON_CALL_UP,i,0);
        }
    }
    for (int j = 1;j < N_FLOORS ;j++) {
        if (e->queue[j][BUTTON_CALL_DOWN] == 1) {
            elev_set_button_lamp(BUTTON_CALL_DOWN,j,1);
        }
        else {
            elev_set_button_lamp(BUTTON_CALL_DOWN,j,0);
        }
    }
    for (int k = 0; k < N_FLOORS; k++) {
        if (e->queue[k][BUTTON_COMMAND] == 1) {
            elev_set_button_lamp(BUTTON_COMMAND,k,1);
        }
        else {
            elev_set_button_lamp(BUTTON_COMMAND,k,0);
        }
    }

}


elev_motor_direction_t queue_floor_inbetween(elevator_t *e) {
    if (e->floor == N_FLOORS-1) {
        if (e->queue[e->floor][BUTTON_CALL_DOWN]||  e->queue[e->floor][BUTTON_COMMAND]) {
            return DIRN_UP;
        }
    }
    if (e->floor == 0) {
        if (e->queue[e->floor][BUTTON_CALL_UP] || e->queue[e->floor][BUTTON_COMMAND]) {
            return DIRN_DOWN;
        }
    }
    if (e->prevDir == DIRN_UP) {
        if (e->queue[e->floor][BUTTON_CALL_DOWN]|| e->queue[e->floor][BUTTON_CALL_UP] || e->queue[e->floor][BUTTON_COMMAND]) {
            return DIRN_DOWN;
        }
    }
    if (e->prevDir == DIRN_DOWN) {
        if (e->queue[e->floor][BUTTON_CALL_DOWN]|| e->queue[e->floor][BUTTON_CALL_UP] || e->queue[e->floor][BUTTON_COMMAND]) {
            return DIRN_UP;
        }
    }
    return queue_choose_direction(e,0);
}
