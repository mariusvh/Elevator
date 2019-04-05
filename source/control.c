#include "elev.h"
#include "queue.h"
#include "io.h"
#include <stdio.h>


void control_update_floor(elevator_t *e) {
    int tempFloor = elev_get_floor_sensor_signal();

    if (tempFloor == -1) {
        return;
    }
    e->floor = tempFloor;
    elev_set_floor_indicator(e->floor);
}


void control_secure_range(){
    if (elev_get_floor_sensor_signal() == N_FLOORS - 1) {
        elev_set_motor_direction(DIRN_DOWN);
    } else if (elev_get_floor_sensor_signal() == 0) {
        elev_set_motor_direction(DIRN_UP);
    }
}



void control_update_direction(elevator_t *e, elev_motor_direction_t dirn) {
    e->prevDir = e->dir;
    e->dir = dirn;
    elev_set_motor_direction(dirn);
}
