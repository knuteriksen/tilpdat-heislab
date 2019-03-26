


typedef enum {INIT, IDLE, MOVING, STOP, ESTOP} state;


void init(); //set current state to INIT
void set_state(state s); //changes the state to s
