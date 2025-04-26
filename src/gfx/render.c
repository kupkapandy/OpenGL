#include "render.h"

// Create buffers properly add data to them
// Create shaders properly link them using program
static void processInput(void){
  float multi = 1.0f;
  if(glfwGetKey(window.window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    multi = 4.0f;
  if(glfwGetKey(window.window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window.window, 1);
  if (glfwGetKey(window.window, GLFW_KEY_W) == GLFW_PRESS){
    vec3 tmp;
    glm_vec3_scale(renderer.cam.camFront, multi * camSpeed * window.deltaTime, tmp);
    glm_vec3_add(renderer.cam.camPos, tmp, renderer.cam.camPos);
  }
  if (glfwGetKey(window.window, GLFW_KEY_S) == GLFW_PRESS){
    vec3 tmp;
    glm_vec3_scale(renderer.cam.camFront, multi * camSpeed * window.deltaTime, tmp);
    glm_vec3_sub(renderer.cam.camPos, tmp, renderer.cam.camPos);
  }
  if (glfwGetKey(window.window, GLFW_KEY_A) == GLFW_PRESS){
    vec3 tmp;
    glm_cross(renderer.cam.camFront, renderer.cam.camUp, tmp);
    glm_normalize(tmp);

    glm_vec3_mulsubs(tmp, multi * camSpeed * window.deltaTime, renderer.cam.camPos);
  }
  if (glfwGetKey(window.window, GLFW_KEY_D) == GLFW_PRESS){
    vec3 tmp;
    glm_cross(renderer.cam.camFront, renderer.cam.camUp, tmp);
    glm_normalize(tmp);

    glm_vec3_muladds(tmp, multi * camSpeed * window.deltaTime, renderer.cam.camPos);
  }

  if (glfwGetKey(window.window, GLFW_KEY_J) == GLFW_PRESS)
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  if (glfwGetKey(window.window, GLFW_KEY_L) == GLFW_PRESS)
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

static void createShaders() {
  GLuint vertexShader = createShader(GL_VERTEX_SHADER, "res/shaders/basic.vs");
  GLuint fragmentShader = createShader(GL_FRAGMENT_SHADER, "res/shaders/basic.fs");
  createProgram(&renderer.program, 2, vertexShader, fragmentShader);
}

static void createBuffers() {
  createVAO(&renderer.vao);
  createVBO(&renderer.vbo, GL_ARRAY_BUFFER, GL_STATIC_DRAW);
  createVBO(&renderer.ebo, GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);

  loadImage("res/images/texture.png");


  attribVAO(renderer.vao, renderer.vbo, 0, 3, GL_FLOAT, sizeof(vec3) + sizeof(vec2), 0);
  attribVAO(renderer.vao, renderer.vbo, 1, 2, GL_FLOAT, sizeof(vec3) + sizeof(vec2), sizeof(vec3));
}

void createRenderer() {
  createWindow();
  createBuffers();
  createShaders();
  createChunk();
  createCam();
}

static struct vector initalizeArray(){
  return (struct vector){
    malloc(sizeof(struct vertex) * 32768),
    32768,
    0,
  };
}

void pushToArray(struct vector *vec, struct vertex val){
  if(vec->amountOfElements >= vec->currentLen - 1){
    vec->currentLen *= 2;
    struct vertex *tmp = realloc(vec->vector, vec->currentLen * sizeof(struct vertex));
    vec->vector = tmp;

  }

  vec->vector[vec->amountOfElements++] = val;
}

void renderStuff() {
  mat4 model = GLM_MAT4_IDENTITY_INIT;
  mat4 view = GLM_MAT4_IDENTITY_INIT;
  mat4 proj = GLM_MAT4_IDENTITY_INIT;

  int modelLoc = glGetUniformLocation(renderer.program, "model");
  int viewLoc = glGetUniformLocation(renderer.program, "view");
  int projLoc = glGetUniformLocation(renderer.program, "proj");

  glm_translate(view, (vec3){0.0f, 0.0f, -3.0f});
  glm_perspective(glm_rad(45.0f), (float)WIDTH/(float)HEIGHT, 0.1f, 1000.0f, proj);

  while(!glfwWindowShouldClose(window.window)) {
    vec3 tmp;
    glm_vec3_add(renderer.cam.camPos, renderer.cam.camFront, tmp);
    glm_lookat(renderer.cam.camPos, tmp, renderer.cam.camUp, view);

    glUseProgram(renderer.program);
    glBindVertexArray(renderer.vao.handle);

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (const float *)model);
    glUniformMatrix4fv(viewLoc, 1,  GL_FALSE, (const float *)view);
    glUniformMatrix4fv(projLoc, 1,  GL_FALSE, (const float *)proj);

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    processInput();
    getDeltaTime();

    uint32_t indicesRender[131072 * 2] = {0};
    uint32_t triangleCnt = 0;

    for(int i = 0; i < CHUNKCNTCUBIC; ++i){
      struct vector verticesRender = initalizeArray();

      uint32_t indexIdx = 0;

      // i / (CHUNKCNT * CHUNKCNT)
      // (i / CHUNKCNT) % CHUNKCNT
      // i % CHUNKCNT

      /* TODO: FIX THIS SHIT */

      for(int x = 0; x < CHUNKSIZE; ++x){
        for(int y = 0; y < CHUNKSIZE; ++y){
          for(int z = 0; z < CHUNKSIZE; ++z){
            if((z == CHUNKSIZE - 1 && i % CHUNKCNT != CHUNKCNT - 1 && renderer.chunks[i + 1]->block[x][y][0].blockID != 0) || renderer.chunks[i]->block[x][y][z + 1].blockID != 0){
              updateFaces(&verticesRender, indicesRender, &indexIdx, i, (ivec3){x, y, z}, 0);
            }
            if((z == 0 && i % CHUNKCNT != 0 && renderer.chunks[i - 1]->block[x][y][z].blockID != 0) || renderer.chunks[i]->block[x][y][z - 1].blockID != 0){
              updateFaces(&verticesRender, indicesRender, &indexIdx, i, (ivec3){x, y, z}, 4);
            }
            if(y == CHUNKSIZE - 1 || renderer.chunks[i]->block[x][y + 1][z].blockID != 0){
              updateFaces(&verticesRender, indicesRender, &indexIdx, i, (ivec3){x, y, z}, 16);
            }
            if(y == 0 || renderer.chunks[i]->block[x][y - 1][z].blockID != 0){
              updateFaces(&verticesRender, indicesRender, &indexIdx, i, (ivec3){x, y, z}, 20);
            }
            if(x == CHUNKSIZE - 1 || renderer.chunks[i]->block[x + 1][y][z].blockID != 0){
              updateFaces(&verticesRender, indicesRender, &indexIdx, i, (ivec3){x, y, z}, 8);
            }
            if(x == 0 || renderer.chunks[i]->block[x - 1][y][z].blockID != 0){
              updateFaces(&verticesRender, indicesRender, &indexIdx, i, (ivec3){x, y, z}, 12);
            }
          }
        }
      }

      bufferVBO(renderer.vbo, verticesRender.vector, sizeof(struct vertex) * verticesRender.amountOfElements);
      bufferVBO(renderer.ebo, indicesRender, sizeof(uint32_t) * indexIdx);

      glDrawElements(GL_TRIANGLES, indexIdx, GL_UNSIGNED_INT, 0);

      triangleCnt += verticesRender.amountOfElements / 2;
      //printf("TRIANGLES COUNTER: %u\n", triangleCnt);

      free(verticesRender.vector);
    }

    glfwSwapBuffers(window.window);
    glfwPollEvents();

    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
      printf("GL ERROR: %x\n", err);
    }
  }
}
