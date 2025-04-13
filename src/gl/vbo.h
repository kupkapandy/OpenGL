#ifndef VBO_H
#define VBO_H

#include "../util/util.h"

struct VBO {
  GLuint handle;
  GLenum type;
  GLenum usage;
};

struct VBO createVBO(GLenum type, GLenum usage);
void bindVBO(struct VBO);
void bufferVBO(struct VBO vbo, void *data, size_t cnt);
void deleteVBO(struct VBO vbo);

#endif
