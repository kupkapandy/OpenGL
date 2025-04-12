#ifndef TIME_H
#define TIME_H

#include "util/util.h"

struct time {
  double deltaTime;
  double curFrame;
  double lastFrame;
  double lastFrameSecond;
  uint32_t fps;
};

struct time initDeltaTime(void);
void getDeltaTime(struct time *state);

#endif
