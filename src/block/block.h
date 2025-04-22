#ifndef BLOCK_H
#define BLOCK_H

#include "../util/util.h"

#define NOFV 24 /* Number Of Vertices */
#define NOFI 36 /* Number Of Indices */

typedef enum blockID_t {
  debug = 0,
  air = 1,
  dirt = 2,
  grass = 3,
  stone = 4,
} blockID;

typedef enum blockAttrib_t {
  solid = 0,
  transparent = 1,
} blockAttrib;

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

  blockID blockID;
  blockAttrib blockAttributes;
  uint8_t atlasIdx;
};

extern struct cube cube;

#endif
