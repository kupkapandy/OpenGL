#ifndef CAMERA_H
#define CAMERA_H

#include "../util/util.h"

struct Camera {
  vec3 camPos;
  vec3 camFront;
  vec3 camRight;
  vec3 camUp;
  vec3 dir;

  float yaw;
  float pitch;
};

void createCam(void);

#endif
