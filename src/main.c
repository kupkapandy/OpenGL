#include "gfx/render.h"

void init(void) {
  createRenderer();
}

void update(void) {

}

void renderLoop(void) {
  renderStuff();
}

void delete(void) {
  deleteVAO(renderer.vao);
  deleteVBO(renderer.ebo);
  deleteVBO(renderer.vbo);
  deleteProgram(renderer.program);
  deleteChunks();

  glfwTerminate();
  exit(0);
}


int main(void) {
  init();
  renderStuff();
  delete();
  return 0;
}


