#include "render.h"

void makeCircle(body *circle){
  float rot = radians(0.5f);
  vec3 v1 = {0, circle->radius, 0.0f};
  vec3 v2 = {circle->radius, 0, 0.0f};

  for(int i = 0; i < NOFT; ++i){
    circle->vertices[i * 3] = circle->pos;
    circle->vertices[i * 3 + 1].x = v1.x + circle->pos.x;
    circle->vertices[i * 3 + 1].y = v1.y + circle->pos.y;
    circle->vertices[i * 3 + 2].x = v2.x + circle->pos.x;
    circle->vertices[i * 3 + 2].y = v2.y + circle->pos.y;

    float x = v1.x;
    float y = v1.y;

    v1.x = (x * cos(rot) - y * sin(rot));
    v1.y = (x * sin(rot) + y * cos(rot));

    x = v2.x;
    y = v2.y;

    v2.x = (x * cos(rot) - y * sin(rot));
    v2.y = (x * sin(rot) + y * cos(rot));

  }
}

void accelerateBody(body *circle, float acceleration){
  if(!circle->onGround)
    circle->velocity.y += acceleration;
}

void moveBodyVelocity(body *circle, float deltaTime){
  accelerateBody(circle, -ACCELERATION * deltaTime);

  if(circle->pos.x - circle->radius <= -1.0f && fabs(circle->velocity.y) <= 0.009f)
    circle->onGround = 1;
  else
    circle->onGround = 0;

  circle->pos.x += circle->velocity.x;
  circle->pos.y += circle->velocity.y;


  printf("%.8f %.8f | %.8f %.8f | %1d\n", circle->pos.x, circle->pos.y, circle->velocity.x, circle->velocity.y, circle->onGround);

}

