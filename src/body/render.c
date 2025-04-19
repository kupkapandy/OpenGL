#include "render.h"

struct body initBody(float zoffset){
  struct body body;
  memset(&body, 0, sizeof(body));
  makeCube(&body, 0.3f, -zoffset);

  return body;
}

void makeCircle(struct body *circle){
  float rot = radians(360.0f / NOFV * 3);
  vec3 v1 = {0, circle->radius, 0.0f};
  vec3 v2 = {-circle->radius * sin(rot), circle->radius * cos(rot), 0.0f};

  for(int i = 0; i < NOFV / 3; ++i){
    float angle = (float)i / (NOFV / 3.0f) * -2.0f * M_PI;

    circle->vertices[i * 3].pos[0] = circle->pos[0];
    circle->vertices[i * 3].pos[1] = circle->pos[1];
    circle->vertices[i * 3].pos[2] = circle->pos[2];

    circle->vertices[i * 3 + 1].pos[0] = v1[0] + circle->pos[0];
    circle->vertices[i * 3 + 1].pos[1] = v1[1] + circle->pos[1];
    circle->vertices[i * 3 + 1].pos[2] = v1[2] + circle->pos[2];

    circle->vertices[i * 3 + 2].pos[0] = v2[0] + circle->pos[0];
    circle->vertices[i * 3 + 2].pos[1] = v2[1] + circle->pos[1];
    circle->vertices[i * 3 + 2].pos[2] = v2[2] + circle->pos[2];

    float rVal = sin(angle) * 0.5f + 0.5f;
    float gVal = sin(angle + 2.0f) * 0.5f + 0.5f;
    float bVal = sin(angle + 4.0f) * 0.5f + 0.5f;

    circle->vertices[i * 3 + 0].color[0] = 0.5f;
    circle->vertices[i * 3 + 0].color[1] = 0.5f;
    circle->vertices[i * 3 + 0].color[2] = 0.5f;

    circle->vertices[i * 3 + 1].color[0] = rVal;
    circle->vertices[i * 3 + 1].color[1] = gVal;
    circle->vertices[i * 3 + 1].color[2] = bVal;

    circle->vertices[i * 3 + 2].color[0] = rVal;
    circle->vertices[i * 3 + 2].color[1] = gVal;
    circle->vertices[i * 3 + 2].color[2] = bVal;

    float x = v1[0];
    float y = v1[1];

    v1[0] = (x * cos(rot) - y * sin(rot));
    v1[1] = (x * sin(rot) + y * cos(rot));

    x = v2[0];
    y = v2[1];

    v2[0] = (x * cos(rot) - y * sin(rot));
    v2[1] = (x * sin(rot) + y * cos(rot));
  }
}

void makeCube(struct body *cube, float len, float zoffset){
  cube->vertices[0].texture[0] = 1.0f;
  cube->vertices[0].texture[1] = 1.0f;

  cube->vertices[1].texture[0] = 1.0f;
  cube->vertices[1].texture[1] = 0.0f;

  cube->vertices[2].texture[0] = 0.0f;
  cube->vertices[2].texture[1] = 0.0f;

  cube->vertices[3].texture[0] = 0.0f;
  cube->vertices[3].texture[1] = 1.0f;

  cube->vertices[0].pos[0] = -0.5f;
  cube->vertices[0].pos[1] = -0.5f;
  cube->vertices[0].pos[2] = -0.5f + zoffset;

  cube->vertices[1].pos[0] =  0.5f;
  cube->vertices[1].pos[1] = -0.5f;
  cube->vertices[1].pos[2] = -0.5f + zoffset;

  cube->vertices[2].pos[0] = 0.5f;
  cube->vertices[2].pos[1] = 0.5f;
  cube->vertices[2].pos[2] = -0.5f + zoffset;

  cube->vertices[3].pos[0] = -0.5f;
  cube->vertices[3].pos[1] = 0.5f;
  cube->vertices[3].pos[2] = -0.5f + zoffset;

  cube->vertices[4].pos[0] = -0.5f;
  cube->vertices[4].pos[1] = -0.5f;
  cube->vertices[4].pos[2] = 0.5f + zoffset;

  cube->vertices[5].pos[0] =  0.5f;
  cube->vertices[5].pos[1] = -0.5f;
  cube->vertices[5].pos[2] = 0.5f + zoffset;

  cube->vertices[6].pos[0] = 0.5f;
  cube->vertices[6].pos[1] = 0.5f;
  cube->vertices[6].pos[2] = 0.5f + zoffset;

  cube->vertices[7].pos[0] = -0.5f;
  cube->vertices[7].pos[1] = 0.5f;
  cube->vertices[7].pos[2] = 0.5f + zoffset;

  // front
  cube->indices[0] = 0;
  cube->indices[1] = 1;
  cube->indices[2] = 2;
  cube->indices[3] = 0;
  cube->indices[4] = 3;
  cube->indices[5] = 2;

  // back
  cube->indices[6] = 4;
  cube->indices[7] = 5;
  cube->indices[8] = 6;
  cube->indices[9] = 4;
  cube->indices[10] = 7;
  cube->indices[11] = 6;

  // left
  cube->indices[12] = 0;
  cube->indices[13] = 4;
  cube->indices[14] = 7;
  cube->indices[15] = 0;
  cube->indices[16] = 3;
  cube->indices[17] = 7;

  // right
  cube->indices[18] = 1;
  cube->indices[19] = 5;
  cube->indices[20] = 6;
  cube->indices[21] = 1;
  cube->indices[22] = 2;
  cube->indices[23] = 6;

  // up
  cube->indices[24] = 6;
  cube->indices[25] = 2;
  cube->indices[26] = 3;
  cube->indices[27] = 6;
  cube->indices[28] = 7;
  cube->indices[29] = 3;

  // down
  cube->indices[30] = 5;
  cube->indices[31] = 1;
  cube->indices[32] = 0;
  cube->indices[33] = 5;
  cube->indices[34] = 4;
  cube->indices[35] = 0;
}

void accelerateBody(struct body *circle, double acceleration){
  if(!circle->onGround)
    circle->velocity[1] += acceleration;
}

void moveBodyVelocity(struct body *circle, double deltaTime){
  accelerateBody(circle, -ACCELERATION * deltaTime);

  if(circle->pos[1] - circle->radius + circle->velocity[1] * deltaTime < -1){
    circle->pos[1] = circle->radius - 1;
    circle->velocity[1] *= -0.6f;
  }else{
    circle->pos[1] += circle->velocity[1] * deltaTime;
  }

  if(circle->pos[1] + circle->radius + circle->velocity[1] * deltaTime > 1){
    circle->pos[1] = 1 - circle->radius;
    circle->velocity[1] *= -0.6f;
  }else{
    circle->pos[1] += circle->velocity[1] * deltaTime;
  }

  if(circle->pos[0] - circle->radius + circle->velocity[0] * deltaTime < -1){
    circle->pos[0] = circle->radius - 1;
    circle->velocity[0] *= -0.45f;
  }else{
    circle->pos[0] += circle->velocity[0] * deltaTime;
  }

  if(circle->pos[0] + circle->radius + circle->velocity[0] * deltaTime > 1){
    circle->pos[0] = 1 - circle->radius;
    circle->velocity[0] *= -0.45f;
  }else{
    circle->pos[0] += circle->velocity[0] * deltaTime;
  }

  //printf("%.8f %.8f | %.8f %.8f | %1d\n", circle->pos.x, circle->pos.y, circle->velocity.x, circle->velocity.y, circle->onGround);

}

