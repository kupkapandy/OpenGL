#include "vbo.h"

struct VBO createVBO(GLenum type, GLenum usage){
  struct VBO vbo = {
    .type = type,
    .usage = usage,
  };

  glGenBuffers(1, &vbo.handle);
  glBindBuffer(vbo.type, vbo.handle);
  return vbo;
}

void bindVBO(struct VBO vbo){
  glBindBuffer(vbo.type, vbo.handle);
}

void unbindVBO(struct VBO vbo){
  glBindBuffer(vbo.type, 0);
}

void bufferVBO(struct VBO vbo, void *data, size_t cnt){
  bindVBO(vbo);
  glBufferData(vbo.type, cnt, data, vbo.usage);
}

void deleteVBO(struct VBO vbo){
  glDeleteBuffers(1, &vbo.handle);
}
