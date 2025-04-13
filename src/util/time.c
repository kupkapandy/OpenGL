#include "time.h"

struct time initDeltaTime(void){
  struct time state;

  state.curFrame = 0.0f;
  state.lastFrame = 0.0f;
  state.lastFrameSecond = 0.0f;

  state.deltaTime = 0.0f;
  state.fps = 0.0f;

  return state;
}

void getDeltaTime(struct time *state){
  static float fps = 0.0f;

  state->curFrame = glfwGetTime();
  state->deltaTime = state->curFrame - state->lastFrame;
  state->lastFrame = state->curFrame;

  ++fps;

  if(state->curFrame - state->lastFrameSecond >= 1.0f){
    state->lastFrameSecond = state->curFrame;
    state->fps = (int)fps;

    fps = 0.0f;

    printf("FPS: %d %f\n", state->fps, state->deltaTime);
  }
}
