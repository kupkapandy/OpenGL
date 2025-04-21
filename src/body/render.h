#ifndef RENDER_H
#define RENDER_H

#include "../block/block.h"
#include "../gfx/window.h"
#include "../gfx/camera.h"
#include "../gfx/vao.h"

#define ACCELERATION 0.98067 * 2.5

struct global {
  struct Window window;
};

struct renderer {
  struct Camera cam;

  struct VAO vao;
  struct VBO vbo, ebo;

  GLuint program;
};

// make it global
extern struct global global;
extern struct renderer renderer;

void initBody(float zoffset);
void makeCube(float zoffset);
void applyTextureCube(uint8_t atlasIdx);

#endif
