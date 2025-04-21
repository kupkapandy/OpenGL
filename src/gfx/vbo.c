#include "vbo.h"

void createVBO(struct VBO *vbo, GLenum type, GLenum usage){
  vbo->type = type;
  vbo->usage = usage;

  glGenBuffers(1, &vbo->handle);
  glBindBuffer(vbo->type, vbo->handle);
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
