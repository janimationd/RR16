#ifndef LOCATION_H_
#define LOCATION_H_

#include <cmath>

// A location in the arena, measured in inches.
class Location {
public:
  // 'x' is measured horizontally from the left wall
  float x;
  // 'y' is vertically measured from the bottom wall
  float y;

  Location(float xx, float yy) {
    x = xx;
    y = yy;
  }

  Location() {
    x = 0;
    y = 0;
  }

  // calculate the distance between me and 'l'
  float distanceTo(Location l) {
    float distX = l.x - x;
    float distY = l.y - y;
    return std::sqrt(distX * distX + distY * distY);
  }
};

// returns true if location is reliable, false otherwise (unreliable locations happen when sensor output is unreliable)
// puts the current location of the center of the robot into 'loc'
bool getLocation(Location &loc) {
  float x = 0;  // the x position back from the distance sensor logic
  float y = 0;  // the y position back from the distance sensor logic
  loc = Location(x, y);
  return true;
}

#endif
