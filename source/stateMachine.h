#include "channels.h"
#include "elev.h"
//#include "io.h"
#include "timer.h"
#include "queue.h"

/**
* @file
* @brief Contains functions to be called if certain events are triggered
*/


typedef enum state {IDLE, MOVING, DOOR_OPEN, EMERGENCY_STOP} elev_state;

/**
* @brief Initialize elevator:
*Move eleavtor to well defined state.
*Reset queue matrix.
*Update current floor and set floor indicator.
*Switch state to @c IDLE.
* @param void.
*/
void state_init (void);

/**
* @brief Updates current floor if floor sensor is triggered.
* Updates @c beetween_floors depending on @c current_direction
* @param void.
*/
void state_update_current_floor (void);

/**
* @brief Opens door, sets all orders at @c current_floor to 0 and stops elevator
* if necessary. Switches state to @c DOOR_OPEN.
* @param void.
*/
void state_open_door (void);

/**
* @brief Closes door and switches state to @c IDLE.
* @param void.
*/
void state_close_door (void);

/**
* @brief Stops elevator, set all orders in matrix to 0, close door and turn on
* emergency stop button lamp. Switches state to @c EMERGENCY_STOP.
* @param void.
*/
void state_emergency_stop_button_pushed (void);

/**
* @brief Turns off emergency stop button lamp and switches state to @c IDLE.
* @param void.
*/
void state_emergency_stop_button_released (void);
/**
* @brief Calculates @c current_direction and set motor direction to
* @c current_direction. Switches state to @c MOVING if elevator should move,
* or @c DOOR_OPEN if elevator should open door.
* @param void.
*/
void state_execute_new_order (void); //executes new order if there is any

/**
* @brief Returns @c current_floor
* @param void.
* @return @c current_floor
*/
int state_get_current_floor(void);

/**
* @brief Returns @c current_direction
* @param void.
* @return @c current_direction
*/
int state_get_current_direction(void);
