#include "body/render.h"
#include "block/block.h"
#include "gfx/shader.h"
#include "gfx/texture.h"
#include "world/chunk.h"
#include "world/world.h"
#include "util/time.h"

struct global global;
struct renderer renderer;
struct cube cube;
struct world world;

static void processInput(void){
  float multi = 1.0f;
  if(glfwGetKey(global.window.window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    multi = 4.0f;
  if(glfwGetKey(global.window.window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(global.window.window, 1);
  if (glfwGetKey(global.window.window, GLFW_KEY_W) == GLFW_PRESS){
    vec3 tmp;
    glm_vec3_scale(renderer.cam.camFront, multi * camSpeed * global.window.deltaTime, tmp);
    glm_vec3_add(renderer.cam.camPos, tmp, renderer.cam.camPos);
  }
  if (glfwGetKey(global.window.window, GLFW_KEY_S) == GLFW_PRESS){
    vec3 tmp;
    glm_vec3_scale(renderer.cam.camFront, multi * camSpeed * global.window.deltaTime, tmp);
    glm_vec3_sub(renderer.cam.camPos, tmp, renderer.cam.camPos);
  }
  if (glfwGetKey(global.window.window, GLFW_KEY_A) == GLFW_PRESS){
    vec3 tmp;
    glm_cross(renderer.cam.camFront, renderer.cam.camUp, tmp);
    glm_normalize(tmp);

    glm_vec3_mulsubs(tmp, multi * camSpeed * global.window.deltaTime, renderer.cam.camPos);
  }
  if (glfwGetKey(global.window.window, GLFW_KEY_D) == GLFW_PRESS){
    vec3 tmp;
    glm_cross(renderer.cam.camFront, renderer.cam.camUp, tmp);
    glm_normalize(tmp);

    glm_vec3_muladds(tmp, multi * camSpeed * global.window.deltaTime, renderer.cam.camPos);
  }

  if (glfwGetKey(global.window.window, GLFW_KEY_J) == GLFW_PRESS)
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  if (glfwGetKey(global.window.window, GLFW_KEY_L) == GLFW_PRESS)
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void init(void){
  initBody(4.0f);
  initCam();
  initTime();
  initChunks();
  createChunk();
  initWindow();

  GLuint vertexShader = createShader(GL_VERTEX_SHADER, "res/shaders/basic.vs");
  GLuint fragmentShader = createShader(GL_FRAGMENT_SHADER, "res/shaders/basic.fs");
  createProgram(&renderer.program, 2, vertexShader, fragmentShader);

  createVAO(&renderer.vao);
  createVBO(&renderer.vbo, GL_ARRAY_BUFFER, GL_STATIC_DRAW);
  createVBO(&renderer.ebo, GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);

  loadImage("res/images/texture.png");

  bufferVBO(renderer.vbo, cube.vertices, sizeof(cube.vertices));
  bufferVBO(renderer.ebo, cube.indices, sizeof(cube.indices));
  attribVAO(renderer.vao, renderer.vbo, 0, 3, GL_FLOAT, sizeof(vertex), 0);
  attribVAO(renderer.vao, renderer.vbo, 1, 2, GL_FLOAT, sizeof(vertex), sizeof(vec3));
}

void update(void){

}

void renderLoop(void){
  mat4 model, proj, view;

  glm_mat4_identity(model);
  glm_mat4_identity(view);
  glm_mat4_identity(proj);

  glm_translate(view, (vec3){0.0f, 0.0f, -3.0f});
  glm_perspective(glm_rad(45.0f), (float)global.window.width / (float)global.window.height, 0.1f, 1000.0f, proj);

  int modelLoc = glGetUniformLocation(renderer.program, "model");
  int viewLoc = glGetUniformLocation(renderer.program, "view");
  int projLoc = glGetUniformLocation(renderer.program, "proj");

  while(!glfwWindowShouldClose(global.window.window)){
    //glm_rotate_at(model, (vec3){0.0f, 0.0f, -2.0f}, glm_rad(180.0f) * global.window.deltaTime, (vec3){0.5f, 1.0f, 0.0f});

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (const float *)model);
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, (const float *)proj);

    getDeltaTime();
    processInput();

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(renderer.program);
    glBindVertexArray(renderer.vao.handle);

    vec3 tmp;
    glm_vec3_add(renderer.cam.camPos, renderer.cam.camFront, tmp);
    glm_lookat(renderer.cam.camPos, tmp, renderer.cam.camUp, view);

    /*
    for(int i = 0; i < 32; ++i){
      for(int j = 0; j < 32; ++j){
        for(int k = 0; k < 32; ++k){
          glm_translate(view, (vec3){-i, -j, -k + -20.0f});

          glUniformMatrix4fv(viewLoc, 1, GL_FALSE, (const float *)view);
          glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void *)(4 * 6 * 0)); // wow


          glm_translate(view, (vec3){i, j, k + 20.0f});
        }
      }
    }
    */

    for(int i = 0; i < CHUNKCNTCUBIC; ++i){
      glm_translate(view, (vec3){
        world.chunks[i]->posInWorld[0] * (CHUNKSIZE * 2),
        world.chunks[i]->posInWorld[1] * (CHUNKSIZE * 2),
        world.chunks[i]->posInWorld[2] * (CHUNKSIZE * 2),
      });
      for(int j = 0; j < CHUNKSIZECUBIC; ++j){
        uint8_t x = j / (CHUNKSIZE * CHUNKSIZE);
        uint8_t y = j / CHUNKSIZE % CHUNKSIZE;
        uint8_t z = j % CHUNKSIZE;
        glm_translate(view, (vec3){
          -x,
          -y,
          -z,
        });

        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, (const float *)view);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void *)(4 * 6 * 0));

        glm_translate(view, (vec3){
          x,
          y,
          z,
        });
      }
      glm_translate(view, (vec3){
        -world.chunks[i]->posInWorld[0] * (CHUNKSIZE * 2),
        -world.chunks[i]->posInWorld[1] * (CHUNKSIZE * 2),
        -world.chunks[i]->posInWorld[2] * (CHUNKSIZE * 2),
      });
    }

    bufferVBO(renderer.vbo, cube.vertices, sizeof(cube.vertices));

    glfwSwapBuffers(global.window.window);
    glfwPollEvents();
  }
}

void delete(void){
  deleteVAO(renderer.vao);
  deleteVBO(renderer.vbo);
  deleteVBO(renderer.ebo);
  deleteProgram(renderer.program);
  deleteChunks();

  glfwTerminate();
}

int main(void){
  init();
  renderLoop();
  delete();
  return 0;
}


