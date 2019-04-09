#include <stdio.h>

#include "queue.h"
#include "elev.h"

//create queue matrix
int queue_matrix [N_FLOORS][N_BUTTONS] = {} ;

 //sets alN_BUTTONSrix values to 0 and turns off lights
void queue_reset_queue_matrix(void) {
  for (int floor = 0; floor < N_FLOORS; floor++) {
    for (int button = 0; button < N_BUTTONS; button++) {
      queue_matrix[floor][button] = 0;
      if (((floor == 0) && (button == BUTTON_CALL_DOWN)) || //check if invalid command
      ((floor == (N_FLOORS-1)) && (button == BUTTON_CALL_UP))) {
        continue;
      }
      elev_set_button_lamp(button, floor, 0);
    }
  }
}

//reset orders at floor "floor" and turns off lights
void queue_reset_floor (int floor){
    for (int button = 0; button < N_BUTTONS; button++) {
      queue_matrix[floor][button] = 0;
    }
    if (floor == 0) {
      elev_set_button_lamp(BUTTON_COMMAND, floor, 0);
      elev_set_button_lamp(BUTTON_CALL_UP, floor, 0);
    }
    else if ((floor > 0) && (floor < (N_FLOORS -1))) {
      elev_set_button_lamp(BUTTON_COMMAND, floor, 0);
      elev_set_button_lamp(BUTTON_CALL_UP, floor, 0);
      elev_set_button_lamp(BUTTON_CALL_DOWN, floor, 0);
    }

    else if (floor == (N_FLOORS -1)) {
      elev_set_button_lamp(BUTTON_COMMAND, floor, 0);
      elev_set_button_lamp(BUTTON_CALL_DOWN, floor, 0);
    }

}

//set orders and turns on lights
void queue_update_matrix(void) {
  for (int floor = 0; floor < N_FLOORS; floor++) {

    if (floor == 0) {

      if (elev_get_button_signal(BUTTON_COMMAND, floor)) {
        queue_matrix[floor][BUTTON_COMMAND] = 1;
        elev_set_button_lamp(BUTTON_COMMAND, floor, 1);
      }

      if (elev_get_button_signal(BUTTON_CALL_UP, floor)) {
        queue_matrix[floor][BUTTON_CALL_UP] = 1;
        elev_set_button_lamp(BUTTON_CALL_UP, floor, 1);
      }
    }

    else if ((floor > 0) && (floor < (N_FLOORS -1))) {
      for (int button = 0; button < N_BUTTONS; button++) {
        if (elev_get_button_signal(button, floor)) {
          queue_matrix[floor][button] = 1;
          elev_set_button_lamp(button, floor, 1);
        }
      }
    }

    else if (floor == (N_FLOORS -1)) {
      if (elev_get_button_signal(BUTTON_COMMAND, floor)) {
        queue_matrix[floor][BUTTON_COMMAND] = 1;
        elev_set_button_lamp(BUTTON_COMMAND, floor, 1);
      }

      if (elev_get_button_signal(BUTTON_CALL_DOWN, floor)) {
        queue_matrix[floor][BUTTON_CALL_DOWN] = 1;
        elev_set_button_lamp(BUTTON_CALL_DOWN, floor, 1);
      }
    }
  }
}


//checks if floor sensor matches BUTTON_COMMAND orders in queue_matrix. floor is floor_sensor
bool queue_cab_right_floor(int floor) {
  return( queue_matrix[floor][N_BUTTONS - 1] == 1 ) ;
}

//checks if BUTTON_CALL_UP OR BUTTON_CALL_DOWN at floor in queue_matrix matches current direction. floor is floor_sensor
bool queue_right_direction(int floor, int current_dir) {
  return( ((queue_matrix[floor][BUTTON_CALL_UP] == 1) && (current_dir == 1)) ||
  ((queue_matrix[floor][BUTTON_CALL_DOWN] == 1) && (current_dir == -1)) );
}

//checks if elevator should stop if current direction does not equel order direction
bool queue_wrong_direction_stop (int floor, int current_dir){
    return( ((current_dir != DIRN_UP) && (queue_matrix[floor][BUTTON_CALL_UP] == 1) && (queue_order_below(floor) == false)) ||
    ((current_dir != DIRN_DOWN) && (queue_matrix[floor][BUTTON_CALL_DOWN] == 1) && (queue_order_above(floor) == false)) );
}

//returns true if elevator should stop. floor is floor_sensor
bool queue_should_elevator_stop(int floor, int current_dir) {
  bool ret_value = ( queue_cab_right_floor(floor) ||
  queue_right_direction(floor, current_dir) ||
  queue_wrong_direction_stop(floor, current_dir) );
  return ret_value;
}

//returns true if there is order above elevator
bool queue_order_above (int floor) {
  if (floor < N_FLOORS -1) {
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
bool queue_order_below(int floor) {
  if (floor > 0) {
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

bool queue_order_same_floor(int floor) {
  for (int button = 0; button < N_BUTTONS; button ++){
    if (queue_matrix[floor][button] == 1) {
      return true;
    }
  }
  return false;
}

//calculates next direction of elevator
int queue_choose_direction (int floor, int between_floors, int current_dir) {
  if (current_dir != DIRN_UP) {
    if (queue_order_below(floor) ||
    (queue_order_same_floor(floor) && (between_floors == 1))){
      return DIRN_DOWN;
    }
    else if (queue_order_above(floor) ||
    (queue_order_same_floor(floor) && (between_floors == -1))) {
      return DIRN_UP;
    }
  }

  else if (current_dir != DIRN_DOWN) {
    if (queue_order_above(floor) ||
    (queue_order_same_floor(floor) && (between_floors == -1))) {
      return DIRN_UP;
    }
    else if (queue_order_below(floor) ||
    (queue_order_same_floor(floor) && (between_floors == 1))){
      return DIRN_DOWN;
    }
  }
  return DIRN_STOP;
}

bool queue_matrix_empty(int current_floor) {
  return (!(queue_order_above(current_floor) || queue_order_below(current_floor) || queue_order_same_floor(current_floor)));
}
