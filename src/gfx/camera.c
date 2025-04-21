#include "camera.h"

struct camera cam = {
  .camPos = {0.0f, 0.0f, 3.0f},
  .camFront = {0.0f, 0.0f, -1.0f},
  .camRight = {1.0f, 0.0f, 0.0f},
  .camUp = {0.0f, 1.0f, 0.0f},

  .yaw = -90.0f,
  .pitch = 0.0f,
};

struct camera camInit(){
  cam.camFront[0] = cos(glm_rad(cam.yaw)) * cos(glm_rad(cam.pitch));
  cam.camFront[1] = sin(glm_rad(cam.pitch));
  cam.camFront[2] = sin(glm_rad(cam.yaw)) * cos(glm_rad(cam.pitch));

  return cam;
}
