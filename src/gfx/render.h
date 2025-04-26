#ifndef RENDER_H
#define RENDER_H

#include "../block/block.h"
#include "../util/time.h"

#include "../gfx/vao.h"
#include "../gfx/shader.h"
#include "../gfx/camera.h"
#include "../gfx/texture.h"
#include "../gfx/window.h"
#include "../world/chunk.h"

struct renderer {
  struct Camera cam;

  struct VAO vao;
  struct VBO vbo, ebo;

  // The skeleton of a block
  struct chunk *chunks[CHUNKCNTCUBIC];

  GLuint program;
};




extern struct renderer renderer;

void createRenderer();
void renderStuff();
void applyTextureCube(uint8_t atlasIdx);
void pushToArray(struct vector *vec, struct vertex val);

#endif
