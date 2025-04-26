#include "camera.h"
#include "../gfx/render.h"

void createCam(void){
  renderer.cam = (struct Camera){
    .yaw = -90.0f,
    .pitch = 0.0f,

    .camPos = {0.0f, 0.0f, 3.0f},
    .camRight = {1.0f, 0.0f, 0.0f},
    .camUp = {0.0f, 1.0f, 0.0f},
    .camFront = {
      cos(glm_rad(-90.0f)) * cos(glm_rad(0.0f)),
      sin(glm_rad(0.0f)),
      sin(glm_rad(-90.0f)) * cos(glm_rad(0.0f)),
    },
  };

  glm_normalize(renderer.cam.camFront);
}
