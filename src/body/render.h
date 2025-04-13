#ifndef RENDER_H
#define RENDER_H

#include "../util/util.h"

#define NOFV 36
#define ACCELERATION 0.98067 * 2.5

typedef struct vertex_t{
  vec3 pos;
  vec3 color;
} vertex;

typedef struct body_t{
  vertex vertices[NOFV];
  vec3 indices[NOFV / 3];

  vec3 pos;
  vec3 velocity;

  float radius;
  bool onGround;
} body;

void makeCircle(body *circle);
void makeCube(body *cube, float len);
void moveBodyVelocity(body *circle, double deltaTime);
void accelerateBody(body *circle, double acceleration);

#endif
