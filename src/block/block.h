#ifndef BLOCK_H
#define BLOCK_H

#include "../util/util.h"

#define NOFV 24 /* Number Of Vertices */
#define NOFI 36 /* Number Of Indices */

enum blockType {
  debug = 0,
  dirt = 1,
  grass = 2,
  stone = 3,
};

typedef struct vertex_t {
  vec3 pos;
  vec2 texture;
} vertex;

struct cube {
  vertex vertices[NOFV];
  uint32_t indices[NOFI];

  vec3 pos;

  /* For example if block have other texture on top or down,
   * we will need to know it, so we will just change it
   * (bad english) :-)
  */

  uint8_t blockType;
  uint8_t atlasIdx;
};

#endif
