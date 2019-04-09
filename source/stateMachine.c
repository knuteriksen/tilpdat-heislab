#include "stateMachine.h"

#include <stdio.h>

int current_floor; //current floor variable

int current_direction; //last direction elevator had. -1 is down, 0 is idle, 1 is up

int between_floors; // -1 if under current floor, 1 if above current floor, 0 else

static elev_state state;

int state_get_current_floor(void) {
  return current_floor;
}

void state_update_current_floor(void) {
  if (elev_get_floor_sensor_signal() != -1) {
    current_floor = elev_get_floor_sensor_signal();
    if (current_direction == DIRN_DOWN) {
      between_floors = -1;
    }
    else if (current_direction ==DIRN_UP) {
      between_floors = 1;
    }
    else if (current_direction == DIRN_STOP) {
      between_floors = 0;
    }
  }
}


//initialize elevator
void state_init (void){
  while (elev_get_floor_sensor_signal() == -1){ //move elevator if between floors
    elev_set_motor_direction(DIRN_UP);
  }

  elev_set_motor_direction(DIRN_STOP); //stop elevator
  current_direction = DIRN_STOP;
  queue_reset_queue_matrix(); //reset all orders and turns off all lights
  state_update_current_floor(); //updates current floor
  elev_set_floor_indicator(current_floor); //turns on floor indicator on current floor
  state = IDLE; //sets state to IDLE
}


void state_open_door (void) {

  elev_set_door_open_lamp(1); //opens door
  timer_start_timer(); //starts timer
  current_floor = elev_get_floor_sensor_signal();  //find out if this is necesary
  queue_reset_floor(current_floor);  //resets orders at current floor and turns off lights at current floor


  switch (state) {

    case (IDLE):
      state = DOOR_OPEN;
      break;

    case (MOVING):
      elev_set_motor_direction(DIRN_STOP);
      state = DOOR_OPEN;
      break;

    case (DOOR_OPEN):
      state = DOOR_OPEN;
      break;

    case (EMERGENCY_STOP):
      state = EMERGENCY_STOP;
      break;

  }
}

void state_close_door (void) {

  elev_set_door_open_lamp(0); //closes door

  switch (state) {

    case (IDLE):
      state = IDLE;
      break;

    case (MOVING):
      state = IDLE;
      break;

    case (DOOR_OPEN):
      state = IDLE;
      break;

    case (EMERGENCY_STOP):
      state = EMERGENCY_STOP;
      break;
  }
}

void state_emergency_stop_button_pushed (void) {

  elev_set_motor_direction (DIRN_STOP); //stops elevator
  queue_reset_queue_matrix(); //resets all orders and turns of all lights
  elev_set_door_open_lamp (0); //closes door
  elev_set_stop_lamp (1); // turns on emergency stop lamp

  switch (state) {

    case (IDLE):
      state = EMERGENCY_STOP;
      break;

    case (MOVING):
      state = EMERGENCY_STOP;
      break;

    case (DOOR_OPEN):
      state = EMERGENCY_STOP;
      break;

    case (EMERGENCY_STOP):
      state = EMERGENCY_STOP;
      break;
  }
}

void state_emergency_stop_button_released (void) {

  elev_set_stop_lamp(0);  //tursn of stop light

  switch (state) {

    case (IDLE):
      state = IDLE;
      break;

    case (MOVING):
      state = IDLE;
      break;

    case (DOOR_OPEN):
      state = IDLE;
      break;

    case (EMERGENCY_STOP):
      state = IDLE;
      break;
  }
}

void state_execute_new_order (void) {

  switch (state) {

    case (IDLE):
      current_direction = queue_choose_direction(current_floor, between_floors, current_direction);
      elev_set_motor_direction (current_direction); //sets motor direction to new calculated direction;

      state = MOVING;
      break;

    case (MOVING):
      state = MOVING;
      break;

    case (DOOR_OPEN):
      state = DOOR_OPEN;
      break;

    case (EMERGENCY_STOP):
      state = EMERGENCY_STOP;
      break;
  }
}

int state_get_current_direction(void) {
  return current_direction;
}
