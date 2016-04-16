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

#endif
