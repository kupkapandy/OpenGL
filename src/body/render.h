#ifndef RENDER_H
#define RENDER_H

#include "../util/util.h"

#define NOFV 8
#define ACCELERATION 0.98067 * 2.5

typedef struct vertex_t{
  vec3 pos;
  vec3 color;
  vec2 texture;
} vertex;

struct body{
  vertex vertices[NOFV];
  uint32_t indices[36];

  vec3 pos;
  vec3 velocity;

  float radius;
  bool onGround;
} ;

struct body initBody(float zoffset);
void makeCircle(struct body *circle);
void makeCube(struct body *cube, float len, float zoffset);
void moveBodyVelocity(struct body *circle, double deltaTime);
void accelerateBody(struct body *circle, double acceleration);

#endif
