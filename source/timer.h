#include <stdbool.h>
#include <time.h>

void start_timer(void);

bool time_is_up(void);

static time_t start_time;
