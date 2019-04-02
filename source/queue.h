#include "elev.h"

#define N_BUTTONS_2 3
#define N_FLOORS_2 4

void queue_reset_queue_matrix(void);   //reset all values of queue matrix to 0 and turns off light

void queue_reset_floor (int floor); //reset orders at floor "floor" and turns off light

void queue_update_matrix(void); // set orders and turns on light

void queue_print_que_matrix(); //prints the queue_matrix

// queue_int get_order(int queue_matrix[N_FLOORS][N_BUTTONS]); trenger vi denne?

bool queue_cab_right_floor(int floor); //checks if floor sensor matches elevator orders in queue_matrix. floor is floor_sensor

bool queue_right_direction (int floor, int current_dir);  //checks if order direction in queue_matrix matches current direction floor is floor_sensor

bool queue_wrong_direction_stop (int floor, int current_dir); //checks if elevator should stop if current direction does not equel order direction

bool queue_should_elevator_stop (int floor);  //returns true if elevator should stop. floor is floor_sensor

bool queue_order_above (int floor); //returns true if there is order above elevator

bool queue_order_below (int floor); //returns true if there is order below elevator

int queue_choose_direction (int floor, int current_dir); //calculates next direction of elevator when elevator is stopped.
