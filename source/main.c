#include <stdio.h>


#include "elev.h"
#include "stateMachine.h"
#include "queue.h"
#include "timer.h"
#include "io.h"


int main() {
    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }

    //printf("Press STOP button to stop elevator and exit program.\n");

    state_init(); //state is now in IDLE
    int c_floor = get_current_floor();
    int c_direction = get_current_direction();

    while (1) {

      queue_update_matrix ();
      state_update_current_floor();
      c_floor = get_current_floor();
      c_direction = get_current_direction();

      if (elev_get_floor_sensor_signal() != -1)
        elev_set_floor_indicator(c_floor);

      if (queue_should_elevator_stop(elev_get_floor_sensor_signal(), c_direction)) {
        state_open_door();
      }

      if (time_is_up()) {
        state_close_door();
      }

      if (elev_get_stop_signal()) {
        state_emergency_stop_button_pushed();
        while (elev_get_stop_signal());
        state_emergency_stop_button_released();
      }

      if (!queue_matrix_empty(get_current_floor())) {
        state_execute_new_order();
      }

  }

    return 0;
}
