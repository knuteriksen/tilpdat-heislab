#include "channels.h"
#include "elev.h"
#include "io.h"
#include "queue.h"


typedef enum {IDLE, MOVING, DOOR_OPEN, EMERGENCY_STOP} state;

void FSM(void);

void state_init (void); //initialize elevator

void state_update_current_floor (void); //updates current floor

void state_open_door (void); // if queue_should_elevator_stop == true

void state_close_door (void); // if door has been open for 3 sec

void state_emergency_stop_button_pushed (void); //if emergency stop button is pushed

void state_emergency_stop_button_released (void); //if emergency stop button is released

void state_execute_new_order (void); //executes new order if there is any


//kom denne pushen med
