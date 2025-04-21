#include "render.h"

struct cube initBody(float zoffset){
  struct cube body;
  memset(&body, 0, sizeof(body));
  makeCube(&body, -zoffset);
  applyTextureCube(&body, 90);

  return body;
}

void makeCube(struct cube *cube, float zoffset){
  // front
  cube->vertices[0].pos[0] = -1.0f;
  cube->vertices[0].pos[1] = -1.0f;
  cube->vertices[0].pos[2] = 1.0f + zoffset;
  cube->vertices[1].pos[0] = 1.0f;
  cube->vertices[1].pos[1] = -1.0f;
  cube->vertices[1].pos[2] = 1.0f + zoffset;
  cube->vertices[2].pos[0] = 1.0f;
  cube->vertices[2].pos[1] = 1.0f;
  cube->vertices[2].pos[2] = 1.0f + zoffset;
  cube->vertices[3].pos[0] = -1.0f;
  cube->vertices[3].pos[1] = 1.0f;
  cube->vertices[3].pos[2] = 1.0f + zoffset;

  // back
  cube->vertices[4].pos[0] = -1.0f;
  cube->vertices[4].pos[1] = -1.0f;
  cube->vertices[4].pos[2] = -1.0f + zoffset;
  cube->vertices[5].pos[0] = 1.0f;
  cube->vertices[5].pos[1] = -1.0f;
  cube->vertices[5].pos[2] = -1.0f + zoffset;
  cube->vertices[6].pos[0] = 1.0f;
  cube->vertices[6].pos[1] = 1.0f;
  cube->vertices[6].pos[2] = -1.0f + zoffset;
  cube->vertices[7].pos[0] = -1.0f;
  cube->vertices[7].pos[1] = 1.0f;
  cube->vertices[7].pos[2] = -1.0f + zoffset;

  // left
  cube->vertices[8].pos[0] = -1.0f;
  cube->vertices[8].pos[1] = -1.0f;
  cube->vertices[8].pos[2] = 1.0f + zoffset;
  cube->vertices[9].pos[0] = -1.0f;
  cube->vertices[9].pos[1] = -1.0f;
  cube->vertices[9].pos[2] = -1.0f + zoffset;
  cube->vertices[10].pos[0] = -1.0f;
  cube->vertices[10].pos[1] = 1.0f;
  cube->vertices[10].pos[2] = -1.0f + zoffset;
  cube->vertices[11].pos[0] = -1.0f;
  cube->vertices[11].pos[1] = 1.0f;
  cube->vertices[11].pos[2] = 1.0f + zoffset;

  // right
  cube->vertices[12].pos[0] = 1.0f;
  cube->vertices[12].pos[1] = -1.0f;
  cube->vertices[12].pos[2] = 1.0f + zoffset;
  cube->vertices[13].pos[0] = 1.0f;
  cube->vertices[13].pos[1] = -1.0f;
  cube->vertices[13].pos[2] = -1.0f + zoffset;
  cube->vertices[14].pos[0] = 1.0f;
  cube->vertices[14].pos[1] = 1.0f;
  cube->vertices[14].pos[2] = -1.0f + zoffset;
  cube->vertices[15].pos[0] = 1.0f;
  cube->vertices[15].pos[1] = 1.0f;
  cube->vertices[15].pos[2] = 1.0f + zoffset;

  // up
  cube->vertices[16].pos[0] = -1.0f;
  cube->vertices[16].pos[1] = 1.0f;
  cube->vertices[16].pos[2] = 1.0f + zoffset;
  cube->vertices[17].pos[0] = 1.0f;
  cube->vertices[17].pos[1] = 1.0f;
  cube->vertices[17].pos[2] = 1.0f + zoffset;
  cube->vertices[18].pos[0] = 1.0f;
  cube->vertices[18].pos[1] = 1.0f;
  cube->vertices[18].pos[2] = -1.0f + zoffset;
  cube->vertices[19].pos[0] = -1.0f;
  cube->vertices[19].pos[1] = 1.0f;
  cube->vertices[19].pos[2] = -1.0f + zoffset;

  // down
  cube->vertices[20].pos[0] = -1.0f;
  cube->vertices[20].pos[1] = -1.0f;
  cube->vertices[20].pos[2] = 1.0f + zoffset;
  cube->vertices[21].pos[0] = 1.0f;
  cube->vertices[21].pos[1] = -1.0f;
  cube->vertices[21].pos[2] = 1.0f + zoffset;
  cube->vertices[22].pos[0] = 1.0f;
  cube->vertices[22].pos[1] = -1.0f;
  cube->vertices[22].pos[2] = -1.0f + zoffset;
  cube->vertices[23].pos[0] = -1.0f;
  cube->vertices[23].pos[1] = -1.0f;
  cube->vertices[23].pos[2] = -1.0f + zoffset;

  for(int i = 0; i < 6; ++i){
    cube->indices[i * 6] = i * 4;
    cube->indices[i * 6 + 1] = i * 4 + 1;
    cube->indices[i * 6 + 2] = i * 4 + 2;
    cube->indices[i * 6 + 3] = i * 4;
    cube->indices[i * 6 + 4] = i * 4 + 3;
    cube->indices[i * 6 + 5] = i * 4 + 2;
  }
}

/* Where atlasIdx is the (0,0) point of texture */
void applyTextureCube(struct cube *cube, uint8_t atlasIdx){
  float x = (atlasIdx % 10) / 10.0f;
  float y = 0.1f * roundf(atlasIdx / 10.0f);

  printf("\n%f ; %f\n", x, y);

  cube->vertices[0].texture[0] = x;
  cube->vertices[0].texture[1] = y + 0.1f;
  cube->vertices[1].texture[0] = x + 0.1f;
  cube->vertices[1].texture[1] = y + 0.1f;
  cube->vertices[2].texture[0] = x + 0.1f;
  cube->vertices[2].texture[1] = y;
  cube->vertices[3].texture[0] = x;
  cube->vertices[3].texture[1] = y;

  cube->vertices[4].texture[0] = x + 0.2f;
  cube->vertices[4].texture[1] = y + 0.1f;
  cube->vertices[5].texture[0] = x + 0.1f;
  cube->vertices[5].texture[1] = y + 0.1f;
  cube->vertices[6].texture[0] = x + 0.1f;
  cube->vertices[6].texture[1] = y;
  cube->vertices[7].texture[0] = x + 0.2f;
  cube->vertices[7].texture[1] = y;

  cube->vertices[8].texture[0] = x + 0.3f;
  cube->vertices[8].texture[1] = y + 0.1f;
  cube->vertices[9].texture[0] = x + 0.2f;
  cube->vertices[9].texture[1] = y + 0.1f;
  cube->vertices[10].texture[0] = x + 0.2f;
  cube->vertices[10].texture[1] = y;
  cube->vertices[11].texture[0] = x + 0.3f;
  cube->vertices[11].texture[1] = y;

  cube->vertices[12].texture[0] = x + 0.3f;
  cube->vertices[12].texture[1] = y + 0.1f;
  cube->vertices[13].texture[0] = x + 0.4f;
  cube->vertices[13].texture[1] = y + 0.1f;
  cube->vertices[14].texture[0] = x + 0.4f;
  cube->vertices[14].texture[1] = y;
  cube->vertices[15].texture[0] = x + 0.3f;
  cube->vertices[15].texture[1] = y;

  cube->vertices[16].texture[0] = x + 0.4f;
  cube->vertices[16].texture[1] = y + 0.1f;
  cube->vertices[17].texture[0] = x + 0.5f;
  cube->vertices[17].texture[1] = y + 0.1f;
  cube->vertices[18].texture[0] = x + 0.5f;
  cube->vertices[18].texture[1] = y;
  cube->vertices[19].texture[0] = x + 0.4f;
  cube->vertices[19].texture[1] = y;

  cube->vertices[20].texture[0] = x + 0.5f;
  cube->vertices[20].texture[1] = y;
  cube->vertices[21].texture[0] = x + 0.6f;
  cube->vertices[21].texture[1] = y;
  cube->vertices[22].texture[0] = x + 0.6f;
  cube->vertices[22].texture[1] = y + 0.1f;
  cube->vertices[23].texture[0] = x + 0.5f;
  cube->vertices[23].texture[1] = y + 0.1f;
}


/*
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

*/

