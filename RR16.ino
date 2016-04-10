#include "RR16.h"
#include "Location.h"
#include "Path.h"

int x;
Location g_currloc(0, 0);  // the current location of the robot, measured from its center
//Path g_scorePath(NULL, 0);  // the path to the scoring pegs
//Path g_ringPath(NULL, 0);  // the path to the ring pegs

void setup() {
  x = 0;
  Location *loc = &g_currLoc;
  // put your setup code here, to run once:
  float bob = ARENA_X_LENGTH;
}

void loop() {
  // put your main code here, to run repeatedly:

}
