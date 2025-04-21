#ifndef RENDER_H
#define RENDER_H

#include "../block/block.h"

#define ACCELERATION 0.98067 * 2.5


struct global_t {
  struct window_t {
    GLFWwindow *window;
    uint32_t WIDTH;
    uint32_t HEIGHT;
  } window;

  struct cam_t {
    vec3 camPos;
    vec3 camFront;
    vec3 camRight;
    vec3 camUp;
    vec3 dir;

    float yaw;
    float pitch;
  } cam;


  struct time_t {
    double deltaTime;
    double curFrame;
    double lastFrame;
    double lastFrameSum;
    uint32_t fps;
  } time;
};

struct cube initBody(float zoffset);
void makeCube(struct cube *cube, float zoffset);
void applyTextureCube(struct cube *cube, uint8_t atlasIdx);

#endif
