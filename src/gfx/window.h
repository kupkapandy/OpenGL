#ifndef WINDOW_H
#define WINDOW_H

#include "../util/util.h"
#define TITLE "Learn OpenGL"
#define WIDTH 960
#define HEIGHT 540

struct Window {
  GLFWwindow *window;
  size_t width;
  size_t height;

  double deltaTime;
  double curFrame, lastFrame, lastFrameSecond;
  uint32_t fps;
};

void initWindow();

#endif
