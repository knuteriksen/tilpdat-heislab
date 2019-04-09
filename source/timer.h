#include <stdbool.h>
#include <time.h>

/**
* @file
* @brief Timer to calculate 3 seconds
*/

/**
* @brief Starts timer and sets @c timer_is_active to 1
* @param void.
*/
void timer_start_timer(void);

/**
* @brief Checks if 3 secons has passed since @c timer_start_timer was called
* @param void.
* @return @c true on success, else @c false
*/
bool timer_time_is_up(void);
