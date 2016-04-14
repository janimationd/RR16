#ifndef ACTION_H_
#define ACTION_H_

#include "RR16.h"
#include "Location.h"
#include <vector>

class Action {
public:
  // called once when this action starts
  virtual void start(){}
  // called every tick until this actions completes (and returns true)
  virtual bool step(){}
  // called when the action is done
  virtual void reset(){}

  Action() {
    done = false;
  }

  // whether or not the action is done
  bool done;
};

class Move : public Action {
public:
  Location target;
  Location currLoc;

  Move(float l) : Action() {}

  void start() {
    getLocation(currLoc);
  }

  // calculate the heading to the target location
  // return a clockwise rotation in radians where 0 rad = facing left, or towards the secondary scoring rings
  float getHeading() {
    return 0;
  }

  bool step() {
    float distance = currLoc.distanceTo(target);

    // if we're there
    if (distance <= DIST_TOLERANCE) {
      /// stop motors
      return true;
    }
    else {
      // continue to target
      /// set speed based on distance (slower when closer?)
      float speed = distance < 6 ? distance / 6 + 1 : 1;
      /// calculate orientation/heading
      float heading = getHeading();
      /// adjust speeds to turn
      float rightSpeed = speed + (heading > 0 ? -heading : 0);
      float leftSpeed = speed + (heading < 0 ? heading : 0);
      /// send speed setpoints to the motors
    }
  }

  void reset() {
    done = false;
    currLoc = Location();
  }
};

class RaiseClaws : public Action {
  void start() {

  }

  bool step() {

  }

  void reset() {

  }
};

class DropClaws : public Action {
  void start() {

  }

  bool step() {

  }

  void reset() {

  }
};

class OpenClaw : public Action {
  void start() {

  }

  bool step() {

  }

  void reset() {

  }
};

class CloseClaw : public Action {
  void start() {

  }

  bool step() {

  }

  void reset() {

  }
};

class RotateClaws : public Action {
  void start() {

  }

  bool step() {

  }

  void reset() {

  }
};

class FindLine : public Action {
  void start() {

  }

  bool step() {

  }

  void reset() {

  }
};

class FollowLine : public Action {
  void start() {

  }

  bool step() {

  }

  void reset() {

  }
};

class ActionList {
  std::vector<std::vector<Action>> list;


};

#endif