#include "timer.h"

static time_t start_time;

static int timer_is_active = 0;

void timer_start_timer(void) {

  start_time = time(NULL);
  timer_is_active = 1;
}

bool timer_time_is_up(void) {

  time_t current_time = time(NULL);

  if ((difftime(current_time, start_time) >= 3) && timer_is_active){
    timer_is_active = 0;
    return true;
  }
  return false;
}
