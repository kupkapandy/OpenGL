#ifndef WINDOW_H
#define WINDOW_H

#include "../util/util.h"

#define TITLE "Learn OpenGL"
#define WIDTH 1440
#define HEIGHT 840

void createWindow();

struct Window {
  GLFWwindow *window;
  size_t width;
  size_t height;

  // Because this struct is global all the values of this struct
  // are 0 initalized, so no need for another function to init them
  double deltaTime;
  double curFrame, lastFrame, lastFrameSecond;
  uint32_t fps;
};

extern struct Window window;

#endif
