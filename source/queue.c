#include "queue.h"
#include "elev.h"
#include "io.h"
#include "channels.h"


//create queue matrix
int queue_matrix [N_FLOORS][N_BUTTONS] = {} ;


 //reset all values of queue matrix to 0
void reset_queue_matrix(void) {
  for (int i = 0; i < N_FLOORS; i++) {
    for (int j = 0; j < N_BUTTONS; i++) {
      queue_matrix[i][j] = 0;
    }
  }
}
