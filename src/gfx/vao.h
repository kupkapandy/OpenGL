#ifndef VAO_H
#define VAO_H

#include "vbo.h"

struct VAO {
  GLuint handle;
};

void createVAO(struct VAO *vao);
void bindVAO(struct VAO vao);
void unbindVAO(void);
void attribVAO(struct VAO vao, struct VBO vbo, GLuint idx, GLuint size,
               GLenum type, GLsizei stride, size_t offset);
void deleteVAO(struct VAO vao);

#endif

