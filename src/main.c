#include "render.h"
#include "window.h"
#include "shader.h"

static void processInput(GLFWwindow* window){
  if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, 1);
}

int main(void){
  GLFWwindow *window = initWindow();

  vec3 vertices[960];
  makeCircle(vertices);

  for(int i = 0; i < 360; i++){
    printf("%d: %f %f %f\n", i, vertices[i].x, vertices[i].y, vertices[i].z);
  }

  uint32_t indices[] = {
    0, 1, 2,
    1, 2, 3,
  };

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
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  uint32_t EBO;
  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


  float rotSpeed = radians(90.0f);

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
    glDrawArrays(GL_TRIANGLES, 0, 960);
    glBindVertexArray(0);
    printf("%f\n", curFrame);

    deltaTime = 0.0f;

    makeCircle(vertices);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);


    glfwSwapBuffers(window);
  }

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
  glDeleteProgram(shaderProgram);

  glfwTerminate();
  return 0;
}
