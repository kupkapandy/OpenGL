#include "vao.h"

void createVAO(struct VAO *vao){
  glGenVertexArrays(1, &vao->handle);
  bindVAO(*vao);
}

void bindVAO(struct VAO vao){
  glBindVertexArray(vao.handle);
}

void unbindVAO(){
  glBindVertexArray(0);
}

void attribVAO(struct VAO vao, struct VBO vbo, GLuint idx,
  GLuint size, GLenum type, GLsizei stride, size_t offset){

  bindVAO(vao);
  bindVBO(vbo);

  glVertexAttribPointer(idx, size, type, GL_FALSE, stride, (void *)offset);
  glEnableVertexAttribArray(idx);
}

void deleteVAO(struct VAO vao){
  unbindVAO();
  glDeleteVertexArrays(1, &vao.handle);
}
