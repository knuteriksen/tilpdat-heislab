#include "queue.h"
#include "elev.h"
#include "io.h"
#include "channels.h"


//create queue matrix
int queue_matrix [N_FLOORS][N_BUTTONS] = {} ;


 //reset all values of queue matrix to 0 and turns off lights

 //sets all queue_matrix values to 0 and turns off lights
void reset_queue_matrix(void) {
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
void reset_floor (int floor){
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
void update_matrix(void) {
  for (int floor = 0; floor < N_FLOORS; floor++) {

    if (floor == 0) {

      if (elev_get_button_signal(BUTTON_COMMAND, floor)) {
        queue_matrix[floor][BUTTON_COMMAND] = 1;
        elev_set_button_lamp(BUTTON_COMMAND, floor, 1)
      }

      if (elev_get_button_signal(BUTTON_CALL_UP, floor)) {
        queue_matrix[floor][BUTTON_CALL_UP] = 1;
        elev_set_button_lamp(BUTTON_CALL_UP, floor, 1)
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
        elev_set_button_lamp(BUTTON_COMMAND, floor, 1)
      }

      if (elev_get_button_signal(BUTTON_CALL_DOWN, floor)) {
        queue_matrix[floor][BUTTON_CALL_DOWN] = 1;
        elev_set_button_lamp(BUTTON_CALL_DOWN, floor, 1)
      }
    }
  }
}

//updates current floor and turns corresponding light on
void update_current_floor(int floor) {
  current_floor = floor;
  elev_set_floor_indicator(floor);
}

//prints the queue_matrix
void print_que_matrix() {
  for (int floor = 0; floor < N_FLOORS; floor++) {
    for (int button = 0; button < N_BUTTONS < button ++) {
      printf("%d  ", queue_matrix[floor][button] );
    }
    printf("\n");
  }
}

//
