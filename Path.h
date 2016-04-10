#ifndef PATH_H_
#define PATH_H_

#include "RR16.h"
#include "Location.h"

class Path {
private:
  // a list of Locations that represent the non-circular path
  Location *nodes;
  // the number of nodes in the path
  uint32_t numNodes;
  // the index of the last location we reached
  uint32_t last;

public:
  Path(Location *locs, uint32_t numLocs) {
    last = 0;
    nodes = locs;
    numNodes = numLocs;
  }

  // returns a pointer to the next node to aim for
  

  // determines when we pass nodes, returns true when we are finished on this path
  // you should update currLoc before calling this
  bool update(Location currLoc) {
    // if we're sufficiently close to the next node...
    if (currLoc.distanceTo(nodes[last + 1]) <= DIST_TOLERANCE) {
      // mark that we've reached the next one
      last++;
      
      // check to see if we're done on this path (reached last node)
      if (last == numNodes - 1) {
        // signal that this path is done
        return true;
      }
    }
    return false;
  }

  // resets this path, setting us back to the beginning
  void reset() {
    last = 0;
  }
};

#endif
