#include "time.h"

struct Window window;

void getDeltaTime(){
  window.curFrame = glfwGetTime();
  window.deltaTime = window.curFrame - window.lastFrame;
  window.lastFrame = window.curFrame;

  window.fps++;

  if(window.curFrame - window.lastFrameSecond >= 1.0f){
    window.lastFrameSecond = window.curFrame;
    window.fps = window.fps;


    printf("FPS: %d %f\n", window.fps, window.deltaTime);
    window.fps = 0.0f;
  }
}
