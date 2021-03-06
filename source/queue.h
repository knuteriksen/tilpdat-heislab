#include <stdbool.h>

/**
* @file
* @brief functions and operations on the queue matrix
*/

/**
* @brief Set all values of queue matrix to 0 and turns off all lights
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
* @brief Checks if elevator should stop.
* @param[in] floor .
* @param [in] current_dir .
* @return @c true on success, else @c false
*/
bool queue_should_elevator_stop (int floor, int current_dir);

/**
* @brief Checks if there is no more orders in queue matrix.
* @param[in] floor .
* @return @c true on success, else @c false
*/
bool queue_matrix_empty(int current_floor);

/**
* @brief Calculates next direction of elevator
* @param[in] floor .
* @param[in] between_floors .
* @return @c true on success, else @c false
*/
int queue_choose_direction (int floor, int between_floors, int current_dir);
