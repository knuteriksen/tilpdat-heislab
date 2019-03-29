#include "controller.h"
#include "elev.h"


bool right_floor(int floor) {
  return( queue_matrix[floor][2] == 1 ) ;
}

bool right_direction(int floor) {
  return( ((queue_matrix[floor][0] == 1) && (current_direction == 1)) ||
  ((queue_matrix[floor][1] == 1) && (current_direction == -1)) );
}

bool should_elevator_stop(int floor) {
  return (right_floor(floor) || right_direction(floor) );
}

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
