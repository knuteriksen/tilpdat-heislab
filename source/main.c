/**
* @file
*/

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

    state_init(); //Initialize elevator

    while (1) {
      queue_update_matrix (); //Check for new orders
      state_update_current_floor();

      if (elev_get_floor_sensor_signal() >= 0) // != -1
        elev_set_floor_indicator(state_get_current_floor()); //Update floor indicator if a new flor is reached

      if (queue_should_elevator_stop(elev_get_floor_sensor_signal(), state_get_current_direction())) {
        state_open_door(); //Stop elevator and open door
      }

      if (timer_time_is_up()) {
        state_close_door(); //Close door
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
