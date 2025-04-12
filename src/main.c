#include "render.h"
#include "window.h"
#include "shader.h"
#include "vbo.h"
#include "vao.h"
#include "time.h"

static void processInput(GLFWwindow* window, body *body, double deltaTime){
  if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, 1);
  if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    body->velocity.x += -ACCELERATION * deltaTime;
  if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    body->velocity.x += ACCELERATION * deltaTime;
  if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    body->velocity.y += ACCELERATION * 2.0f * deltaTime;
  if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    body->velocity.y += -ACCELERATION * deltaTime;
}

float deltaTime = 0.0f;

int main(void){
  GLFWwindow *window = initWindow();

  body ball;
  memset(&ball, 0, sizeof(ball));

  ball.radius = 0.1f;
  ball.velocity.x = 0.5f;
  makeCircle(&ball);

  GLuint vertexShader = createShader(GL_VERTEX_SHADER, "res/shaders/basic.vs");
  GLuint fragmentShader = createShader(GL_FRAGMENT_SHADER, "res/shaders/basic.fs");
  GLuint shaderProgram = createProgram(2, vertexShader, fragmentShader);

  struct VBO vbo = createVBO(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
  bufferVBO(vbo, ball.vertices, sizeof(ball.vertices));

  struct VAO vao = createVAO();
  attribVAO(vao, vbo, 0, 3, GL_FLOAT, sizeof(vertex), 0);
  attribVAO(vao, vbo, 1, 3, GL_FLOAT, sizeof(vertex), sizeof(vec3));

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  struct time deltaTime = initDeltaTime();
  while(!glfwWindowShouldClose(window)){

    getDeltaTime(&deltaTime);
    processInput(window, &ball, deltaTime.deltaTime);

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glDrawArrays(GL_TRIANGLES, 0, NOFT * 3);

    moveBodyVelocity(&ball, deltaTime.deltaTime);
    makeCircle(&ball);

    bufferVBO(vbo, ball.vertices, sizeof(ball.vertices));

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  deleteVAO(vao);
  deleteVBO(vbo);
  glDeleteProgram(shaderProgram);

  glfwTerminate();
  return 0;
}
