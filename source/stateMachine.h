#include "channels.h"
#include "elev.h"
#include "io.h"
#include "timer.h"
#include "queue.h"


typedef enum state {IDLE, MOVING, DOOR_OPEN, EMERGENCY_STOP} elev_state;


void state_init (void); //initialize elevator

void state_update_current_floor (void); //updates current floor

void state_open_door (void); // if queue_should_elevator_stop == true

void state_close_door (void); // if door has been open for 3 sec

void state_emergency_stop_button_pushed (void); //if emergency stop button is pushed

void state_emergency_stop_button_released (void); //if emergency stop button is released

void state_execute_new_order (void); //executes new order if there is any

int get_current_floor(void);

int get_current_direction(void);
