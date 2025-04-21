#ifndef WINDOW_H
#define WINDOW_H

#include "../util/util.h"

#define WIDTH 600
#define HEIGHT 600

#define TITLE "Learn OpenGL"

struct Window {
  GLFWwindow *window;
  size_t width, height;
};

GLFWwindow *initWindow(void);

#endif
