#ifndef WORLD_H
#define WORLD_H

#include "chunk.h"
#include "../util/util.h"

struct world {
  struct chunk *chunks[CHUNKCNT * CHUNKCNT * CHUNKCNT];
  /*
   * put something here maybe
   *
  */
};

extern struct world world;

#endif
