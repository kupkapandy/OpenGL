#ifndef VAO_H
#define VAO_H

#include "util/util.h"
#include "vbo.h"

struct VAO {
  GLuint handle;
};

struct VAO createVAO(void);
void bindVAO(struct VAO vao);
void attribVAO(struct VAO vao, struct VBO vbo, GLuint idx, GLuint size,
               GLenum type, GLsizei stride, size_t offset);
void deleteVAO(struct VAO vao);

#endif

