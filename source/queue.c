/**
* @file
*/

#include <stdio.h>

#include "queue.h"
#include "elev.h"

//create queue matrix
int queue_matrix [N_FLOORS][N_BUTTONS] = {} ;


//returns true if there is order above elevator
/**
* @brief Checks if there is any orders above @p floor.
* @param[in] floor .
* @return @c true on success, else @c false
*/
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


/**
* @brief Checks if there is any orders below @p floor.
* @param[in] floor .
* @return @c true on success, else @c false
*/
bool queue_order_below(int floor) { //returns true if there is order below elevator
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


/**
* @brief Checks if there is any orders at @p floor.
* @param[in] floor .
* @return @c true on success, else @c false
*/
bool queue_order_same_floor(int floor) { //returns true if there is order at same flor as elevator is at
  for (int button = 0; button < N_BUTTONS; button ++){
    if (queue_matrix[floor][button] == 1) {
      return true;
    }
  }
  return false;
}

/**
* @brief Checks if @p floor matches elevator cab orders in queue matrix.
* @param[in] floor .
* @return @c true on success, else @c false
*/
bool queue_cab_right_floor_stop(int floor) { //checks if floor sensor matches BUTTON_COMMAND orders in queue_matrix. floor is floor_sensor
  return( queue_matrix[floor][N_BUTTONS - 1] == 1 ) ;
}

/**
* @brief Checks if there is a order at @p floor that matches @p current_dir
*of elevator
* @param[in] floor .
* @param [in] current_dir .
* @return @c true on success, else @c false
*/
bool queue_right_direction_stop(int floor, int current_dir) {//returns true if BUTTON_CALL_UP OR BUTTON_CALL_DOWN at floor in queue_matrix matches current direction
  return( ((queue_matrix[floor][BUTTON_CALL_UP] == 1) && (current_dir == DIRN_UP)) ||
  ((queue_matrix[floor][BUTTON_CALL_DOWN] == 1) && (current_dir == DIRN_DOWN)) );
}

/**
* @brief Checks if there is an order in opposite direction that should be
* executed
* @param[in] floor .
* @param [in] current_dir .
* @return @c true on success, else @c false
*/
bool queue_wrong_direction_stop (int floor, int current_dir){//returns true if elevator should stop when current direction does not equal order direction
    return( ((current_dir != DIRN_UP) && (queue_matrix[floor][BUTTON_CALL_UP] == 1) && (queue_order_below(floor) == false)) ||
    ((current_dir != DIRN_DOWN) && (queue_matrix[floor][BUTTON_CALL_DOWN] == 1) && (queue_order_above(floor) == false)) );
}

 //sets all values in queue_matrix to 0 and turns off all lights
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

//set orders at floor to 0 and turns off all lights at floor
void queue_reset_floor (int floor){
  for (int button = 0; button < N_BUTTONS; button++) {
    if (((floor == 0) && (button == BUTTON_CALL_DOWN)) || //check if invalid command
    ((floor == (N_FLOORS-1)) && (button == BUTTON_CALL_UP))) {
      continue;
    }
    elev_set_button_lamp(button,floor,0);
    queue_matrix[floor][button] = 0;
  }
}

//set new orders and turns on order lights
void queue_update_matrix(void) {
  for (int floor = 0; floor < N_FLOORS; floor++) {
    for (int button = 0; button < N_BUTTONS; button++) {
      if (((floor == 0) && (button == BUTTON_CALL_DOWN)) || //check if invalid command
      ((floor == (N_FLOORS-1)) && (button == BUTTON_CALL_UP))) {
        continue;
      }
      if (elev_get_button_signal(button, floor)) {
        queue_matrix[floor][button] = 1;
        elev_set_button_lamp(button, floor, 1);
      }
    }
  }
}

//returns true if elevator should stop. floor is floor_sensor
bool queue_should_elevator_stop(int floor, int current_dir) {
  return (queue_right_direction_stop(floor, current_dir) ||
  queue_wrong_direction_stop(floor, current_dir) ||
  queue_cab_right_floor_stop(floor));
}

//returns next direction of elevator
int queue_choose_direction (int floor, int between_floors, int current_dir) {
  if (current_dir != DIRN_UP) {
    if (queue_order_below(floor) ||
    (queue_order_same_floor(floor) && (between_floors == 1))){
      return DIRN_DOWN; //if moving down or idle and there is order below current position
    }
    else if (queue_order_above(floor) ||
    (queue_order_same_floor(floor) && (between_floors == -1))) {
      return DIRN_UP; //if moving down or idle and there is order above current position
    }
  }

  else if (current_dir != DIRN_DOWN) {
    if (queue_order_above(floor) ||
    (queue_order_same_floor(floor) && (between_floors == -1))) {
      return DIRN_UP; // if moving up or idle and there is order above current position
    }
    else if (queue_order_below(floor) ||
    (queue_order_same_floor(floor) && (between_floors == 1))){
      return DIRN_DOWN;// if moving up or idle and there is order below current position
    }
  }
  return DIRN_STOP;
}

//returns true if matrix is empty
bool queue_matrix_empty(int current_floor) {
  return (!(queue_order_above(current_floor) || queue_order_below(current_floor) || queue_order_same_floor(current_floor)));
}
