#include "timer.h"

void start_timer(void) {

  start_time = time(NULL);
}

bool time_is_up(void) {

  time_t current_time = time(NULL);

  if (difftime(current_time, start_time) >= 3){
    return true;
  }
  return false;
}
