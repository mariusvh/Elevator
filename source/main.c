#include "elev.h"
#include "queue.h"
#include <stdio.h>



int main() {
    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }

    printf("Press STOP button to stop elevator and exit program.\n");

    //Create Elevator e
    elevator_t el;
    el.floor = -1;
    el.dir = DIRN_STOP;
    el.prevDir = DIRN_STOP;
    el.state = IDLE;
    //queue_reset_matrix(&el);

    //Preparing e for start.
    elev_defined_start(&el);
    printf("%d\n", el.floor);
    printf("%d\n", el.dir);
    printf("%d\n", el.prevDir);
    printf("%d\n", el.state);



    while (1) {
        //Check range
        if (elev_get_floor_sensor_signal() == N_FLOORS - 1) {
            elev_set_motor_direction(DIRN_DOWN);
        } else if (elev_get_floor_sensor_signal() == 0) {
            elev_set_motor_direction(DIRN_UP);
        }


        // Stop elevator and exit program if the stop button is pressed
        if (elev_get_stop_signal()) {
            elev_set_motor_direction(DIRN_STOP);
            break;
        }
        printf("69\n");

        queue_update_matrix(&el);



        /*switch (e.state) {
          case IDLE:

          case MOVE:

          case DOOR_OPEN:

          case STOP:
      }*/
    }

    return 0;
}
