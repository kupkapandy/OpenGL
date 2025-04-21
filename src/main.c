#include "body/render.h"
#include "gfx/window.h"
#include "gfx/shader.h"
#include "gfx/vao.h"
#include "gfx/texture.h"
#include "gfx/camera.h"
#include "util/time.h"

static void processInput(GLFWwindow* window, struct camera *cam, double deltaTime){
  if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, 1);
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
    vec3 tmp;
    glm_vec3_scale(cam->camFront, camSpeed * deltaTime, tmp);
    glm_vec3_add(cam->camPos, tmp, cam->camPos);

  }
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
    vec3 tmp;
    glm_vec3_scale(cam->camFront, camSpeed * deltaTime, tmp);
    glm_vec3_sub(cam->camPos, tmp, cam->camPos);

  }
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
    vec3 tmp;
    glm_cross(cam->camFront, cam->camUp, tmp);
    glm_normalize(tmp);

    glm_vec3_mulsubs(tmp, camSpeed * deltaTime, cam->camPos);
  }
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
    vec3 tmp;
    glm_cross(cam->camFront, cam->camUp, tmp);
    glm_normalize(tmp);

    glm_vec3_muladds(tmp, camSpeed * deltaTime, cam->camPos);
  }
}

extern struct camera cam;

float deltaTime = 0.0f;

int main(void){
  GLFWwindow *window = initWindow();

  struct cube cube = initBody(4.0f);

  GLuint vertexShader = createShader(GL_VERTEX_SHADER, "res/shaders/basic.vs");
  GLuint fragmentShader = createShader(GL_FRAGMENT_SHADER, "res/shaders/basic.fs");
  GLuint shaderProgram = createProgram(2, vertexShader, fragmentShader);

  loadImage("res/images/texture.png");

  struct VAO vao = createVAO();
  struct VBO vbo = createVBO(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
  struct VBO ebo = createVBO(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);

  bufferVBO(vbo, cube.vertices, sizeof(cube.vertices));
  bufferVBO(ebo, cube.indices, sizeof(cube.indices));
  attribVAO(vao, vbo, 0, 3, GL_FLOAT, sizeof(vertex), 0);
  attribVAO(vao, vbo, 1, 2, GL_FLOAT, sizeof(vertex), sizeof(vec3));

  mat4 model;
  glm_mat4_identity(model);

  mat4 view;
  glm_mat4_identity(view);
  glm_translate(view, (vec3){0.0f, 0.0f, -3.0f});

  mat4 proj;
  glm_mat4_identity(proj);
  glm_perspective(glm_rad(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 1000.0f, proj);

  int modelLoc = glGetUniformLocation(shaderProgram, "model");
  int viewLoc = glGetUniformLocation(shaderProgram, "view");
  int projLoc = glGetUniformLocation(shaderProgram, "proj");

  const float radius = 1.0f;
  struct time deltaTime = initDeltaTime();
  while(!glfwWindowShouldClose(window)){
    //glm_rotate_at(model, (vec3){0.0f, 0.0f, -2.0f}, glm_rad(180.0f) * deltaTime.deltaTime, (vec3){0.5f, 1.0f, 0.0f});

    float camX = sin(glfwGetTime()) * radius;
    float camZ = cos(glfwGetTime()) * radius;

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (const float *)model);
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, (const float *)proj);

    getDeltaTime(&deltaTime);
    processInput(window, &cam, deltaTime.deltaTime);

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glBindVertexArray(vao.handle);

    for(int i = 0; i < 64; ++i){
      for(int j = 0; j < 64; ++j){
        for(int k = 0; k < 64; ++k){
          glm_mat4_identity(view);
          vec3 tmp;
          glm_vec3_add(cam.camPos, cam.camFront, tmp);
          glm_lookat(cam.camPos, tmp, cam.camUp, view);
          glm_translate(view, (vec3){-i * 2, -j * 2, -k * 2 + -20.0f});

          glUniformMatrix4fv(viewLoc, 1, GL_FALSE, (const float *)view);
          glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0); // wow
        }
      }
    }

    bufferVBO(vbo, cube.vertices, sizeof(cube.vertices));

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  deleteVAO(vao);
  deleteVBO(vbo);
  deleteVBO(ebo);
  deleteProgram(shaderProgram);

  glfwTerminate();
  return 0;
}
