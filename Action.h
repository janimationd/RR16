#ifndef ACTION_H_
#define ACTION_H_

#include "Windows.h"
#include "RR16.h"
#include "Location.h"
#include <cmath>
#include <vector>

#define M_PI 3.1415f

bool horizontal;
float orientation;
Location position;

class Action {
public:
  // called once when this action starts
  virtual void start(){
    printf("In Action's start!\n");
  }
  // called every tick until this actions completes (and returns true)
  virtual bool step() { 
    printf("In Action's step!\n");
    return false;
  }
  // called when the action is done
  virtual void reset(){
    printf("In Action's reset!\n");
  }

  Action() {
    done = false;
  }

  // whether or not the action is done
  bool done;
};

class Move : public Action {
public:
  Location target;

  Move(Location l) : Action(), target(l) {}

  void start() override {
    
  }

  void getOrientationAndPosition() {
    static const float x = 8.5f;
    float distA = senseDistance('A'); /// calculate distance of sensor(s) A
    float distB = senseDistance('B'); /// calculate distance of sensor B
    float distC = senseDistance('C'); /// calculate distance of sensor C

    float diff = distB - distC;
    orientation = atan(x / diff) + (horizontal ? 0: M_PI / 2);
  }

  // calculate the heading to the target location
  // return a clockwise rotation in radians where 0 rad = facing left, or towards the secondary scoring rings
  float getHeading() {
    static const float x = 8.5f;
    float distB = senseDistance('B');
    float distC = senseDistance('C');

    float diff = distB - distC;
    float orient = atan(x / diff);

    return 0;
  }

  bool step() override {
    getOrientationAndPosition();
    float distance = position.distanceTo(target);

    // if we're there
    if (distance <= DIST_TOLERANCE) {
      /// stop motors
      done = true;
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
    return false;
  }

  void reset() override {
    done = false;
  }
};

class RaiseClaws : public Action {
  void start() override {
    /// set motor speed to raise claws
  }

  bool step() override {
    // check to see if limit switch is pressed
    if (/*limit switch pressed*/true) {
      /// set motor speed to 0
      done = true;
      return true;
    }
    return false;
  }

  void reset() override {
    done = false;
  }
};

class DropClaws : public Action {
  void start() override {
    /// set motor speed to drop claws
  }

  bool step() override {
    // check to see if limit switch is pressed
    if (/*limit switch pressed*/true) {
      /// set motor speed to 0
      done = true;
      return true;
    }
    return false;
  }

  void reset() override {
    done = false;
  }
};

class OpenClaw : public Action {
private:
  unsigned long startTime;
  const static unsigned long duration = 1000;
public:
  void start() override {
    /// set position setpoint for "open"
    //startTime = millis();
  }

  bool step() override {
    // if timer has expired
    if (/*millis() - */startTime >= duration) {
      done = true;
      return true;
    }
    return false;
  }

  void reset() override {
    done = false;
  }
};

class CloseClaw : public Action {
private:
  unsigned long startTime;
  const static unsigned long duration = 1000;
public:
  void start() override {
    /// set position setpoint for "closed"
    //startTime = millis();
  }

  bool step() override {
    // if timer has expired
    if (/*millis() - */startTime >= duration) {
      // we assume motor has stopped
      done = true;
      return true;
    }
    return false;
  }

  void reset() override {
    done = false;
  }
};

class RotateClaws : public Action {
  unsigned long startTime;
  static const unsigned long duration = 250;
  bool cw_dir;

  RotateClaws(bool cw) : Action(), cw_dir(cw) {}

  void start() override {
    if (cw_dir) {
      /// speed setpoint for CW rotation
    }
    else {
      /// speed setpoint for CCW rotation
    }
  }

  bool step() override {
    // if we hit a limit switch
    if (true/*we hit a limit switch*/) {
      /// set motor speed to 0
      done = true;
      return true;
    }
    return false;
  }

  void reset() override {
    done = false;
  }
};

// drive forward until we find a line, then stop immediately
class FindLine : public Action {
  void start() override {

  }

  bool step() override {

  }

  void reset() override {
    done = false;
  }
};

class Timer : public Action {
public:
  unsigned long startTime;
  unsigned long duration;

  // duration in milliseconds
  Timer(unsigned long dur) : Action(), duration(dur) {}

  void start() override {
    #ifdef ARDUINO
      startTime = millis();
    #else
      startTime = GetTickCount();
    #endif
  }

  bool step() override {
    unsigned long currTime;
    #ifdef ARDUINO
      currTime = millis();
    #else
      currTime = GetTickCount();
    #endif

    // check timer
    if (currTime - startTime >= duration) {
      #ifndef ARDUINO
        printf(">>> Timer done.\n");
      #endif
      
      done = true;
      return true;
    }
    return false;
  }

  void reset() override {
    done = false;
  }
};

class ActionList {
public:
  std::vector<std::vector<Action*>> list;

  ActionList() : index(0) {}
  void go() {
    // main loop, for each index
    while (true) {
      // start all members
      for (Action* a : list.at(index)) {
        a->start();
      }

      // all members continue until all are done
      bool someNotDone = true;
      while (someNotDone) {
        for (Action* a : list.at(index)) {
          if (!a->done) {
            a->step();
            someNotDone = false;
          }
        }
        someNotDone = !someNotDone;
      }

      // reset all members
      for (Action* a : list.at(index)) {
        a->reset();
      }

      updateAverageSensorReadings();
      advance();
    }
  }
private:
  unsigned int index;
  void advance() {
    index = (index + 1) % list.size();
  }
};

#endif