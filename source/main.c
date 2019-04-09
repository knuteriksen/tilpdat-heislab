#include <stdio.h>

#include "stateMachine.h"
#include "queue.h"
#include "timer.h"
#include "elev.h"


int main() {
    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }

    state_init(); //state is now in IDLE
    int c_floor = state_get_current_floor();
    int c_direction = state_get_current_direction();

    while (1) {

      queue_update_matrix ();
      state_update_current_floor();
      c_floor = state_get_current_floor();
      c_direction = state_get_current_direction();

      if (elev_get_floor_sensor_signal() != -1)
        elev_set_floor_indicator(c_floor);

      if (queue_should_elevator_stop(elev_get_floor_sensor_signal(), c_direction)) {
        state_open_door();
      }

      if (timer_time_is_up()) {
        state_close_door();
      }

      if (elev_get_stop_signal()) {
        state_emergency_stop_button_pushed();
        while (elev_get_stop_signal());
        state_emergency_stop_button_released();
      }

      if (!queue_matrix_empty(state_get_current_floor())) {
        state_execute_new_order();
      }

  }

    return 0;
}
