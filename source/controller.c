#include "controller.h"
#include "elev.h"

//checks if floor sensor matches BUTTON_COMMAND orders in queue_matrix. floor is floor_sensor
bool right_floor(int floor) {
  return( queue_matrix[floor][N_FLOORS - 1] == 1 ) ;
}

//checks if BUTTON_CALL_UP OR BUTTON_CALL_DOWN at floor in queue_matrix matches current direction floor is floor_sensor
bool right_direction(int floor) {
  return( ((queue_matrix[floor][0] == 1) && (current_direction == 1)) ||
  ((queue_matrix[floor][1] == 1) && (current_direction == -1)) );
}
//returns true if elevator should stop. floor is floor_sensor
bool should_elevator_stop(int floor) {
  return (right_floor(floor) || right_direction(floor) );
}

//returns true if there is order above elevator
bool order_above (int floor) {
  if (floor < 3) {
    for (int f = floor + 1; f < N_FLOORS ; f ++) {
      for (int button = 0; button < N_BUTTONS; button ++){
        if (queue_matrix[f][button] == 1) {
          return true;
        }
      }
    }
  }
  return false;
}

//returns true if there is order below elevator
bool order_below(int floor) {
  if (loor > 0) {
    for (int f = floor - 1; f >= 0 ; f --) {
      for (int button = 0; button < N_BUTTONS; button ++){
        if (queue_matrix[f][button] == 1) {
          return true;
        }
      }
    }
  }
  return false;
}
//
