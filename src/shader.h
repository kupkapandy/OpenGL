#ifndef SHADER_H
#define SHADER_H

#include "util/util.h"

const char *readShader(const char *path);
void shaderLog(GLuint shader);
void programLog(GLuint program);

#endif
