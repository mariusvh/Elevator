#include "elev.h"
#include "io.h"
#include <stdio.h>


void control_update_floor(elevator_t *e) {
    if (elev_get_floor_sensor_signal() == -1) {
        return;
    }
    e->floor = elev_get_floor_sensor_signal(); //vil dette lagres utenfor funksjonskallet??
    elev_set_floor_indicator(e->floor);
}


void control_secure_range(){
    if (elev_get_floor_sensor_signal() == N_FLOORS - 1) {
        elev_set_motor_direction(DIRN_DOWN);
    } else if (elev_get_floor_sensor_signal() == 0) {
        elev_set_motor_direction(DIRN_UP);
    }
}
