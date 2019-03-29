#include "elev.h"
#include "queue.h"

int between_floors; //which floors are the elevator between. 0 is between first and second, 1 is between second and third, 2 is between third and fourth
int current_direction; //last direction elevator had. -1 is down, 0 is idle, 1 is up

//get_order(int queue_matrix[N_FLOORS][N_BUTTONS]);

bool right_floor(int floor); //checks if floor sensor matches elevator orders in queue_matrix. floor is floor_sensor

bool right_direction (int floor);  //checks if order direction in queue_matrix matches current direction floor is floor_sensor
bool should_elevator_stop (int floor);  //returns true if elevator should stop. floor is floor_sensor

bool order_above (void; //returns true if there is order above elevator

bool order_below (); //returns true if there is order below elevator

int choose_direction (); //returns new direction for elevator

void update_between_floors (); //updates between_floors

void update_current_direction (); //updates current direction
