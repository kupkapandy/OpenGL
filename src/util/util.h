#ifndef UTIL_H
#define UTIL_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wfloat-equal"

#include <cglm/cglm.h>
#include <cglm/struct.h>

#pragma GCC diagnostic pop

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>

#define TITLE "Learn OpenGL"
#define WIDTH 1440
#define HEIGHT 840

#define camSpeed 10.0f

#define PI 3.14159265358979f
#define radians(_x) ((_x) * (__typeof__(_x)) (PI / 180.0f))
#define degrees(_x) ((_x) * (__typeof__(_x)) (180.0f / PI))

#endif
