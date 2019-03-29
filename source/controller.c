#include "controller.h"
#include "elev.h"

//checks if floor sensor matches elevator orders in queue_matrix. floor is floor_sensor
bool right_floor(int floor) {
  return( queue_matrix[floor][2] == 1 ) ;
}
//checks if order direction in queue_matrix matches current direction floor is floor_sensor
bool right_direction(int floor) {
  return( ((queue_matrix[floor][0] == 1) && (current_direction == 1)) ||
  ((queue_matrix[floor][1] == 1) && (current_direction == -1)) );
}
//returns true if elevator should stop. floor is floor_sensor
bool should_elevator_stop(int floor) {
  return (right_floor(floor) || right_direction(floor) );
}

//returns true if there is order above elevator
bool order_above (void) {
  if (current_floor < 3) {
    for (int floor = current_floor + 1; floor < N_FLOORS ; floor ++) {
      if ( (queue_matrix[floor][0] == 1) || (queue_matrix[floor][1] == 1) ||
      (queue_matrix[floor][2] == 1) ) {
        return true;
      }
    }
  }
  return false;
}

//returns true if there is order below elevator
bool order_below(void) {
  if (current_floor > 0) {
    for (int floor = current_floor - 1; floor >= 0 ; floor --) {
      if ( (queue_matrix[floor][0] == 1) || (queue_matrix[floor][1] == 1) ||
      (queue_matrix[floor][2] == 1) ) {
        return true;
      }
    }
  }
  return false;
}
//
