#include <stdbool.h>

#include "elev.h"


/**
* @file
* @brief functions and operations on the queue matrix
*/


#define N_BUTTONS_2 3
#define N_FLOORS_2 4


/**
* @brief Set all values of queue matrix to 0 and turn off all lights
* @param void.
*/
void queue_reset_queue_matrix(void);

/**
* @brief Set orders at floor @p floor and turns off light at @p floor
* @param[in] floor .
*/
void queue_reset_floor (int floor);


/**
* @brief Iterates through all buttons and checks if any is pushed.
*If any buttons is pushed the corresponding slot in queue matrix is set to 1
*and corresponding lights are turned on.
* @param void .
*/
void queue_update_matrix(void);

/**
* @brief Checks if @p floor matches elevator cab orders in queue matrix.
* @param[in] floor .
* @return @c true on success, else @c false
*/
bool queue_cab_right_floor(int floor);


/**
* @brief Checks if there is a order at @p floor that matches @p current_dir
*of elevator
* @param[in] floor .
* @return @c true on success, else @c false
*/
bool queue_right_direction (int floor, int current_dir);

bool queue_wrong_direction_stop (int floor, int current_dir); //checks if elevator should stop if current direction does not equel order direction

bool queue_should_elevator_stop (int floor, int current_dir);  //returns true if elevator should stop. floor is floor_sensor

bool queue_order_above (int floor); //returns true if there is order above elevator

bool queue_order_below (int floor); //returns true if there is order below elevato

bool queue_order_same_floor(int floor);

bool queue_matrix_empty(int current_floor);

int queue_choose_direction (int floor, int between_floors); //calculates next direction of elevator when elevator is stopped.
