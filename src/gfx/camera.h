#ifndef CAMERA_H
#define CAMERA_H

#include "../util/util.h"

#define camSpeed 10.0f
#define startPos {0.0f, 0.0f, 3.0f}
#define origin (vec3){0.0f, 0.0f, 0.0f}

struct camera {
  vec3 camPos;
  vec3 camFront;
  vec3 camRight;
  vec3 camUp;
  vec3 dir;

  float yaw;
  float pitch;
};

struct camera camInit();

#endif
