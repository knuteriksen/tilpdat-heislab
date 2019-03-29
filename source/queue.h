
int current_floor; //current floor variable

void reset_queue_matrix(void);   //reset all values of queue matrix to 0 and turns off light

void reset_floor (int floor); //reset orders at floor "floor" and turns off light

void update_matrix(void); // set orders and turns on light

void update_current_floor(int floor);  //updates current floor and turns corresponding light on

void print_que_matrix(); //prints the queue_matrix

//
