#ifndef ACTION_H_
#define ACTION_H_

#include "Location.h"

class Action {
public:
  // called once when this action starts
  virtual void start(){}
  // called every tick until this actions completes (and returns true)
  virtual bool step(){}
  // called when the action is done
  virtual void reset(){}
};

class Move : public Action {
public:
  Location loc;

  Move(Location l) : loc(l) {
    
  }

  void start() {
    
  }

  bool step() {
    
  }

  void reset() {

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

#endif