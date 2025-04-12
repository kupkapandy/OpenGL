#include "render.h"

void makeCircle(body *circle){
  float rot = radians(360.0f / NOFT);
  vec3 v1 = {0, circle->radius, 0.0f};
  vec3 v2 = {-circle->radius * sin(rot), circle->radius * cos(rot), 0.0f};

  for(int i = 0; i < NOFT; ++i){
    float angle = (float)i / NOFT * -2.0f * M_PI;

    circle->vertices[i * 3].pos = circle->pos;

    circle->vertices[i * 3 + 1].pos.x = v1.x + circle->pos.x;
    circle->vertices[i * 3 + 1].pos.y = v1.y + circle->pos.y;

    circle->vertices[i * 3 + 2].pos.x = v2.x + circle->pos.x;
    circle->vertices[i * 3 + 2].pos.y = v2.y + circle->pos.y;

    float rVal = sin(angle) * 0.5f + 0.5f;
    float gVal = sin(angle + 2.0f) * 0.5f + 0.5f;
    float bVal = sin(angle + 4.0f) * 0.5f + 0.5f;

    circle->vertices[i * 3 + 0].color.x = 0.5f;
    circle->vertices[i * 3 + 0].color.y = 0.5f;
    circle->vertices[i * 3 + 0].color.z = 0.5f;

    circle->vertices[i * 3 + 1].color.x = rVal;
    circle->vertices[i * 3 + 1].color.y = gVal;
    circle->vertices[i * 3 + 1].color.z = bVal;

    circle->vertices[i * 3 + 2].color.x = rVal;
    circle->vertices[i * 3 + 2].color.y = gVal;
    circle->vertices[i * 3 + 2].color.z = bVal;

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

  if(circle->pos.y - circle->radius + circle->velocity.y < -1){
    circle->pos.y = circle->radius - 1;
    circle->velocity.y *= -0.8f;
  }else{
    circle->pos.y += circle->velocity.y;
  }

  if(circle->pos.y + circle->radius + circle->velocity.y > 1){
    circle->pos.y = 1 - circle->radius;
    circle->velocity.y *= -0.8f;
  }else{
    circle->pos.y += circle->velocity.y;
  }

  if(circle->pos.x - circle->radius + circle->velocity.x < -1){
    circle->pos.x = circle->radius - 1;
    circle->velocity.x *= -0.45f;
  }else{
    circle->pos.x += circle->velocity.x;
  }

  if(circle->pos.x + circle->radius + circle->velocity.x > 1){
    circle->pos.x = 1 - circle->radius;
    circle->velocity.x *= -0.45f;
  }else{
    circle->pos.x += circle->velocity.x;
  }

  printf("%.8f %.8f | %.8f %.8f | %1d\n", circle->pos.x, circle->pos.y, circle->velocity.x, circle->velocity.y, circle->onGround);

}

