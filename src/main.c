#include "body/render.h"
#include "gl/window.h"
#include "gl/shader.h"
#include "gl/vbo.h"
#include "gl/vao.h"
#include "util/time.h"

static void processInput(GLFWwindow* window, body *body, double deltaTime){
  if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, 1);
  if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    body->velocity[0] += -ACCELERATION * deltaTime;
  if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    body->velocity[0] += ACCELERATION * deltaTime;
  if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    body->velocity[1] += ACCELERATION * 2.0f * deltaTime;
  if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    body->velocity[1] += -ACCELERATION * deltaTime;
  if(glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  if(glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

}

float deltaTime = 0.0f;

int main(void){
  GLFWwindow *window = initWindow();

  body cube;
  memset(&cube, 0, sizeof(cube));
  makeCube(&cube, 0.1f);

  GLuint vertexShader = createShader(GL_VERTEX_SHADER, "res/shaders/basic.vs");
  GLuint fragmentShader = createShader(GL_FRAGMENT_SHADER, "res/shaders/basic.fs");
  GLuint shaderProgram = createProgram(2, vertexShader, fragmentShader);

  struct VBO vbo = createVBO(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
  bufferVBO(vbo, cube.vertices, sizeof(cube.vertices));

  struct VAO vao = createVAO();
  attribVAO(vao, vbo, 0, 3, GL_FLOAT, sizeof(vertex), 0);
  attribVAO(vao, vbo, 1, 3, GL_FLOAT, sizeof(vertex), sizeof(vec3));


  struct time deltaTime = initDeltaTime();

  mat4 model;
  glm_mat4_identity(model);
  glm_rotate(model, glm_rad(45.0f), (vec3){1.0f, 0.0f, 0.0f});

  mat4 view;
  glm_mat4_identity(view);
  glm_translate(view, (vec3){0.0f, 0.0f, -3.0f});

  mat4 proj;
  glm_mat4_identity(proj);
  glm_perspective(glm_rad(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f, proj);

  int modelLoc = glGetUniformLocation(shaderProgram, "model");
  int viewLoc = glGetUniformLocation(shaderProgram, "view");
  int projLoc = glGetUniformLocation(shaderProgram, "proj");

  while(!glfwWindowShouldClose(window)){

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (const float *)model);
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, (const float *)view);
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, (const float *)proj);

    getDeltaTime(&deltaTime);
    processInput(window, &cube, deltaTime.deltaTime);

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glDrawArrays(GL_TRIANGLES, 0, NOFV);

    bufferVBO(vbo, cube.vertices, sizeof(cube.vertices));
    glm_rotate(model, glm_rad(55.0f) * deltaTime.deltaTime, (vec3){0.5f, 1.0f, 0.0f});


    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  deleteVAO(vao);
  deleteVBO(vbo);
  deleteProgram(shaderProgram);

  glfwTerminate();
  return 0;
}
