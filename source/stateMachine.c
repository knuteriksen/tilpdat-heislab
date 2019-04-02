#include "stateMachine.h"

#include "stdio.h"

int current_floor; //current floor variable

int current_direction; //last direction elevator had. -1 is down, 0 is idle, 1 is up

int between_floors; //which floors is the elevator between. 0 is between first and second, 1 is between second and third, 2 is between third and fourth


void state_update_current_floor(int floor) {
  current floor = floor;
}

void state_open_door (void) {

  elev_set_door_open_lamp(1); //opens door
  //start timer               //starts timer
  queue_reset_floor(current_floor)  //resets orders at current floor and turns off lights at current floor

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

  elev_set_stop_lamp(0);

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
