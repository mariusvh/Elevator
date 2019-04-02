#include "queue.h"
#include "elev.h"
#include "io.h"
#include <stdio.h>


void reset_queue_matrix(Elevator e){
  for (int i = 0; i < N_FLOORS; i++) {
    for (int j = 0; j < N_BUTTONS; j++) {
      e.queue[i][j] = 0;
    }
  }
  e.queue[0][1] = -1;
  e.queue[N_FLOORS][0] = -1;
}

void update_queue_matrix(Elevator e){
  for (int i = 0; i < N_FLOORS; i++) {
    for (int j = 0; j < N_BUTTONS; j++) {
      e.queue[i][j] = e.queue[i][j] || elev_get_button_signal(j,i); // j is elev_button_type   BUTTON_CALL_UP = 0, BUTTON_CALL_DOWN = 1, BUTTON_COMMAND = 2
    }
  }
  e.queue[0][1] = -1;
  e.queue[N_FLOORS][0] = -1;
}


int queue_anyOrders(Elevator e){
  for (int i = 0; i < N_FLOORS; i++) {
    for (int j = 0; j < N_BUTTONS; j++) {
      if (e.queue[i][j] == 1) {
        return 1;
      }
    }
  }
  return 0;
}



int queue_ordersAbove(Elevator e){
  for (int i = e.floor + 1; i < N_FLOORS; i++) {
    for (int j = 0; j < N_BUTTONS; j++) {
      if (e.queue[i][j] == 1) {
        return 1;
      }
    }
  }
  return 0;
}

int queue_ordersUnder(Elevator e){
  for (int i = 0; i < e.floor; i++) {
    for (int j = 0; j < N_BUTTONS; j++) {
      if (e.queue[i][j] == 1) {
        return 1;
      }
    }
  }
  return 0;
}

void queue_deleteExecutedOrders(Elevator e, int floor){
  for (int i = 0; i < N_BUTTONS; i++) {
    e.queue[floor][i] == 0;
  }
  e.queue[0][1] = -1;
  e.queue[N_FLOORS][0] = -1;
}

elev_motor_direction_t queue_chooseDirection(Elevator e){
  switch (e.prevdDir) {
    case DIRN_UP:
      if (queue_ordersAbove(e)) {
        return DIRN_UP;
      }
      if (queue_ordersUnder(e)) {

        return DIRN_DOWN;
      }
      return DIRN_STOP;

    case DIRN_DOWN:
      if (queue_ordersUnder(e)) {
        return DIRN_DOWN;
      }
      if (queue_ordersAbove(e)) {
        return DIRN_UP
      }
      return DIRN_STOP;


    case DIRN_STOP:
      if (queue_ordersUnder(e)) {
        return DIRN_DOWN;
      }
      if (queue_ordersAbove(e)) {
        return DIRN_UP
      }
      return DIRN_STOP;

    default:
      return DIRN_STOP;
  }

}

int queue_stopAtFloor(Elevator e) {
  switch (e.dir) {
    case DIRN_UP:
      if (e.queue[e.floor][BUTTON_CALL_UP] || queue[e.floor][BUTTON_COMMAND] || !queue_ordersAbove()) {
        return 1;
      }
      return 0;

    case DIRN_DOWN:
      if (e.queue[e.floor][BUTTON_CALL_DOWN] || queue[e.floor][BUTTON_COMMAND] || !queue_ordersUnder()) {
        return 1;
      }
      return 0;

    default:
      return 1;
  }
}
