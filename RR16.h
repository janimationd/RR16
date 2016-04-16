#ifndef RR16_H_
#define RR16_H_

#include "stdint.h"

// In this file goes information about the arena, the regulations, and our robot
// ... so mainly sizes and distances

#define ARENA_X_LENGTH 96.f  // length of arena [inches]
#define ARENA_Y_WIDTH 48.f  // width of arena [inches]
#define ROBOT_BASE_WIDTH 9.f  // the width of the robot's square base in either of the main axes [inches]
#define RING_PEG_SPACING 8.f  // the spacing between primary ring pegs [inches]
#define SCORING_PEG_SPACING 5.f  // the spacing between secondary scoring pegs [inches]
#define SPEEDBUMP_POSITION 17.f  // horizontal position of left side of speed bump [inches]
#define SPEEDBUMP_THICKNESS 0.75f  // thickness of speed bump [inches]
#define DIST_TOLERANCE 1.f  // distance we are ok with calling "good enough" for pathing purposes [inches]

uint32_t aTotal = 4000;
uint32_t bTotal = 4000;
uint32_t cTotal = 4000;

float senseDistance(char sensor) {
  uint32_t sensor_output = 0;

  switch (sensor) {
  case 'A':
    sensor_output = aTotal / 20;
    break;

  case 'B':
    sensor_output = bTotal / 20;
    break;

  case 'C':
    sensor_output = cTotal / 20;
    break;

  default:
    ;
  }

  // convert ticks to inches;
  return (200.0f / sensor_output - 0.5f) * 12;
}

void updateAverageSensorReadings() {
  #ifdef ARDUINO
    aTotal = (aTotal * 0.95f) + (analogRead(A0));
    bTotal = (bTotal * 0.95f) + (analogRead(A1));
    cTotal = (cTotal * 0.95f) + (analogRead(A2));
  #endif
}

#endif