#include "elev.h"
#include "queue.h"

int between_floors; //which floors are the elevator between. 0 is between first and second, 1 is between second and third, 2 is between third and fourth

int get_order(int queue_matrix[N_FLOORS][N_BUTTONS]);

bool right_floor(); //checks if floor sensor matches orders in queue_matrix

bool right_direction ();  //checks if order direction in queue_matrix matches current direction

bool should_elevator_stop ();  //returns true if elevator should stop

bool order_above (); //returns true if there is order above elevator

bool order_below (); //returns true if there is order below elevator

int choose_direction (); //returns new direction for elevator
