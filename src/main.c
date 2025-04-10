#include "render.h"
#include "window.h"
#include "shader.h"

static void processInput(GLFWwindow* window){
  if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, 1);
}

float deltaTime = 0.0f;

int main(void){
  GLFWwindow *window = initWindow();

  body ball;
  memset(&ball, 0, sizeof(ball));

  ball.radius = 0.1f;
  ball.velocity.x = 10.0f;
  makeCircle(&ball);

  const char *vertexShaderSource = readShader("res/shaders/basic.vs");
  const char *fragmentShaderSource = readShader("res/shaders/basic.fs");

  uint32_t vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  shaderLog(vertexShader);

  uint32_t fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);

  shaderLog(fragmentShader);

  uint32_t shaderProgram;
  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  programLog(shaderProgram);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  /* cast it to non const *
     glShaderSource needs const char *
  */
  free((void *)vertexShaderSource);
  free((void *)fragmentShaderSource);

  uint32_t VAO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  uint32_t VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertex) * NOFT * 3, ball.vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


  float lastFrame = 0.0f;
  float curFrame = 0.0f;
  float deltaTime = 0.0f;

  while(!glfwWindowShouldClose(window)){

    curFrame = glfwGetTime();
    deltaTime = curFrame - lastFrame;
    lastFrame = curFrame;

    processInput(window);

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, NOFT * 3);
    glBindVertexArray(0);

    moveBodyVelocity(&ball, deltaTime);
    makeCircle(&ball);


    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex) * NOFT * 3, ball.vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    deltaTime = 0.0f;


    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteProgram(shaderProgram);

  glfwTerminate();
  return 0;
}
