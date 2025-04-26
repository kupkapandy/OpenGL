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

struct vertex {
  vec3 pos;
  vec2 tex;
};

struct block {
  struct vertex vertices[NOFV];

  blockID blockID;
  blockAttrib blockAttributes;
  uint8_t textureID;
};

static const float vertices[] = {
  0.0f, 0.0f, 1.0f,
  1.0f, 0.0f, 1.0f,
  1.0f, 1.0f, 1.0f,
  0.0f, 1.0f, 1.0f,

  0.0f, 0.0f, 0.0f,
  1.0f, 0.0f, 0.0f,
  1.0f, 1.0f, 0.0f,
  0.0f, 1.0f, 0.0f,

  1.0f, 0.0f, 1.0f,
  1.0f, 0.0f, 0.0f,
  1.0f, 1.0f, 0.0f,
  1.0f, 1.0f, 1.0f,

  0.0f, 0.0f, 1.0f,
  0.0f, 0.0f, 0.0f,
  0.0f, 1.0f, 0.0f,
  0.0f, 1.0f, 1.0f,

  0.0f, 1.0f, 1.0f,
  1.0f, 1.0f, 1.0f,
  1.0f, 1.0f, 0.0f,
  0.0f, 1.0f, 0.0f,

  0.0f, 0.0f, 1.0f,
  1.0f, 0.0f, 1.0f,
  1.0f, 0.0f, 0.0f,
  0.0f, 0.0f, 0.0f,
};

static const unsigned int indices[] = {
  0, 1, 2, 0, 3, 2, // Z+
  4, 5, 6, 4, 7, 6, // Z-
  8, 9, 10, 8, 11, 10, // X+
  12, 13, 14, 12, 15, 14, // X-
  16, 17, 18, 16, 19, 18, // Y+
  20, 21, 22, 20, 23, 22, // Y-
};

extern struct block block;

#endif
