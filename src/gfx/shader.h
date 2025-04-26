#ifndef SHADER_H
#define SHADER_H

#include "../util/util.h"

GLuint createShader(GLenum type, const char *path);
void createProgram(GLuint *shaderProgram, GLuint cnt, ...);
void deleteProgram(GLuint shaderProgram);

#endif
