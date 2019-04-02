#include "elev.h"
#include <stdio.h>
#include "queue.h"
#include "stateMachine.h"



int main() {
    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }

    //printf("Press STOP button to stop elevator and exit program.\n");

    state_init (); //state is now in IDLE

    while (1) {

      queue_update_matrix ();
      state_update_current_floor();

      if (queue_should_elevator_stop()) {
        state_open_door();
      }

      if (time_is_up()) {
        state_close_door();
      }


    }

    /* while (1) {
        // Change direction when we reach top/bottom floor
        if (elev_get_floor_sensor_signal() == N_FLOORS - 1) {
            elev_set_motor_direction(DIRN_DOWN);
        } else if (elev_get_floor_sensor_signal() == 0) {
            elev_set_motor_direction(DIRN_UP);
        }


        Stop elevator and exit program if the stop button is pressed
        if (elev_get_stop_signal()) {
            elev_set_motor_direction(DIRN_STOP);

            break;
        }*/
      }
    return 0;
}
