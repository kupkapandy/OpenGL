#ifndef RENDER_H
#define RENDER_H

#include "util/util.h"

#define NOFT 1800
#define ACCELERATION 0.0098067f

typedef struct body_t{
  vec3 vertices[NOFT * 3];

  vec3 pos;
  vec3 velocity;

  float radius;
  bool onGround;
} body;

void makeCircle(body *circle);
void moveBodyVelocity(body *circle, float deltaTime);
void accelerateBody(body *circle, float acceleration);

#endif
