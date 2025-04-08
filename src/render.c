#include "render.h"

void makeCircle(vec3 *vertices){
  float r = 0.5f;
  float rot = radians(1.0f);
  vec3 v1 = {0.0f, r, 0.0f};
  vec3 v2 = {r, 0.0f, 0.0f};

  for(int i = 0; i < 360; ++i){
    memset(vertices + i * 3, 0.0f, sizeof(vec3));
    vertices[i * 3 + 1] = v1;
    vertices[i * 3 + 2] = v2;

    float x = v1.x;
    float y = v1.y;

    v1.x = x * cos(rot) - y * sin(rot);
    v1.y = x * sin(rot) + y * cos(rot);

    x = v2.x;
    y = v2.y;

    v2.x = x * cos(rot) - y * sin(rot);
    v2.y = x * sin(rot) + y * cos(rot);
  }
}
