#ifndef SHADER_H
#define SHADER_H

#include "util/util.h"

GLuint createShader(GLenum type, const char *path);
GLuint createProgram(GLuint cnt, ...);
void shaderLog(GLuint shader);
void programLog(GLuint program);

#endif
