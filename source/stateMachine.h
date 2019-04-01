


typedef enum {INIT, IDLE, MOVING, STOP, ESTOP} state;

int current_floor; //current floor variable

int between_floors; //which floors is the elevator between. 0 is between first and second, 1 is between second and third, 2 is between third and fourth

int current_direction; //last direction elevator had. -1 is down, 0 is idle, 1 is up

void init(); //set current state to INIT

void set_state(state s); //changes the state to s
