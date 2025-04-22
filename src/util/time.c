#include "time.h"
#include "../body/render.h"

void initTime(){
  global.window.deltaTime = 0.0f;

  global.window.curFrame = 0.0f;
  global.window.lastFrame = 0.0f;
  global.window.lastFrameSecond = 0.0f;

  global.window.fps = 0.0f;
}

void getDeltaTime(){
  global.window.curFrame = glfwGetTime();
  global.window.deltaTime = global.window.curFrame - global.window.lastFrame;
  global.window.lastFrame = global.window.curFrame;

  global.window.fps++;

  if(global.window.curFrame - global.window.lastFrameSecond >= 1.0f){
    global.window.lastFrameSecond = global.window.curFrame;
    global.window.fps = global.window.fps;


    printf("FPS: %d %f\n", global.window.fps, global.window.deltaTime);
    global.window.fps = 0.0f;
  }
}
