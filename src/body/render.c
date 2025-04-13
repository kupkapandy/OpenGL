#include "render.h"

void makeCircle(body *circle){
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

void makeCube(body *cube, float len){

  for(int i = 0; i < NOFV / 3; ++i){
    float angle = (float)i / (NOFV / 3.0f) * -2.0f * M_PI;

    float rVal = sin(angle) * 0.5f + 0.5f;
    float gVal = sin(angle + 2.0f) * 0.5f + 0.5f;
    float bVal = sin(angle + 4.0f) * 0.5f + 0.5f;

    cube->vertices[i * 3 + 0].color[0] = 0.5f;
    cube->vertices[i * 3 + 0].color[1] = 0.5f;
    cube->vertices[i * 3 + 0].color[2] = 0.5f;

    cube->vertices[i * 3 + 1].color[0] = rVal;
    cube->vertices[i * 3 + 1].color[1] = gVal;
    cube->vertices[i * 3 + 1].color[2] = bVal;

    cube->vertices[i * 3 + 2].color[0] = rVal;
    cube->vertices[i * 3 + 2].color[1] = gVal;
    cube->vertices[i * 3 + 2].color[2] = bVal;
  }

  cube->vertices[0].pos[0] = -len;
  cube->vertices[0].pos[1] = len;
  cube->vertices[0].pos[2] = len;
  cube->vertices[1].pos[0] = -len;
  cube->vertices[1].pos[1] = -len;
  cube->vertices[1].pos[2] = len;
  cube->vertices[2].pos[0] = len;
  cube->vertices[2].pos[1] = -len;
  cube->vertices[2].pos[2] = len;
  cube->vertices[3].pos[0] = -len;
  cube->vertices[3].pos[1] = len;
  cube->vertices[3].pos[2] = len;
  cube->vertices[4].pos[0] = len;
  cube->vertices[4].pos[1] = len;
  cube->vertices[4].pos[2] = len;
  cube->vertices[5].pos[0] = len;
  cube->vertices[5].pos[1] = -len;
  cube->vertices[5].pos[2] = len;

  cube->vertices[6].pos[0] = -len;
  cube->vertices[6].pos[1] = len;
  cube->vertices[6].pos[2] = -len;
  cube->vertices[7].pos[0] = -len;
  cube->vertices[7].pos[1] = -len;
  cube->vertices[7].pos[2] = -len;
  cube->vertices[8].pos[0] = len;
  cube->vertices[8].pos[1] = -len;
  cube->vertices[8].pos[2] = -len;
  cube->vertices[9].pos[0] = -len;
  cube->vertices[9].pos[1] = len;
  cube->vertices[9].pos[2] = -len;
  cube->vertices[10].pos[0] = len;
  cube->vertices[10].pos[1] = len;
  cube->vertices[10].pos[2] = -len;
  cube->vertices[11].pos[0] = len;
  cube->vertices[11].pos[1] = -len;
  cube->vertices[11].pos[2] = -len;

  cube->vertices[12].pos[0] = -len;
  cube->vertices[12].pos[1] = len;
  cube->vertices[12].pos[2] = len;
  cube->vertices[13].pos[0] = -len;
  cube->vertices[13].pos[1] = -len;
  cube->vertices[13].pos[2] = len;
  cube->vertices[14].pos[0] = -len;
  cube->vertices[14].pos[1] = -len;
  cube->vertices[14].pos[2] = -len;

  cube->vertices[15].pos[0] = -len;
  cube->vertices[15].pos[1] = len;
  cube->vertices[15].pos[2] = len;
  cube->vertices[16].pos[0] = -len;
  cube->vertices[16].pos[1] = len;
  cube->vertices[16].pos[2] = -len;
  cube->vertices[17].pos[0] = -len;
  cube->vertices[17].pos[1] = -len;
  cube->vertices[17].pos[2] = -len;

  cube->vertices[18].pos[0] = len;
  cube->vertices[18].pos[1] = len;
  cube->vertices[18].pos[2] = len;
  cube->vertices[19].pos[0] = len;
  cube->vertices[19].pos[1] = -len;
  cube->vertices[19].pos[2] = len;
  cube->vertices[20].pos[0] = len;
  cube->vertices[20].pos[1] = -len;
  cube->vertices[20].pos[2] = -len;

  cube->vertices[21].pos[0] = len;
  cube->vertices[21].pos[1] = len;
  cube->vertices[21].pos[2] = len;
  cube->vertices[22].pos[0] = len;
  cube->vertices[22].pos[1] = len;
  cube->vertices[22].pos[2] = -len;
  cube->vertices[23].pos[0] = len;
  cube->vertices[23].pos[1] = -len;
  cube->vertices[23].pos[2] = -len;

  cube->vertices[24].pos[0] = -len;
  cube->vertices[24].pos[1] = len;
  cube->vertices[24].pos[2] = -len;
  cube->vertices[25].pos[0] = len;
  cube->vertices[25].pos[1] = len;
  cube->vertices[25].pos[2] = -len;
  cube->vertices[26].pos[0] = len;
  cube->vertices[26].pos[1] = len;
  cube->vertices[26].pos[2] = len;

  cube->vertices[27].pos[0] = -len;
  cube->vertices[27].pos[1] = len;
  cube->vertices[27].pos[2] = -len;
  cube->vertices[28].pos[0] = -len;
  cube->vertices[28].pos[1] = len;
  cube->vertices[28].pos[2] = len;
  cube->vertices[29].pos[0] = len;
  cube->vertices[29].pos[1] = len;
  cube->vertices[29].pos[2] = len;

  cube->vertices[30].pos[0] = -len;
  cube->vertices[30].pos[1] = -len;
  cube->vertices[30].pos[2] = -len;
  cube->vertices[31].pos[0] = len;
  cube->vertices[31].pos[1] = -len;
  cube->vertices[31].pos[2] = -len;
  cube->vertices[32].pos[0] = len;
  cube->vertices[32].pos[1] = -len;
  cube->vertices[32].pos[2] = len;

  cube->vertices[33].pos[0] = -len;
  cube->vertices[33].pos[1] = -len;
  cube->vertices[33].pos[2] = -len;
  cube->vertices[34].pos[0] = -len;
  cube->vertices[34].pos[1] = -len;
  cube->vertices[34].pos[2] = len;
  cube->vertices[35].pos[0] = len;
  cube->vertices[35].pos[1] = -len;
  cube->vertices[35].pos[2] = len;
}

void accelerateBody(body *circle, double acceleration){
  if(!circle->onGround)
    circle->velocity[1] += acceleration;
}

void moveBodyVelocity(body *circle, double deltaTime){
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

