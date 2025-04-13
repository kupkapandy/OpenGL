#include "window.h"


static void framebufferSizeCallback(GLFWwindow* window, int width, int height){
  glViewport(0, 0, width, height);
}

GLFWwindow *initWindow(void){
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window;

  if((window = glfwCreateWindow(WIDTH, HEIGHT, "Learn OpenGL", NULL, NULL)) == NULL){
    fprintf(stderr, "Failed to create GLFW window\n");
    glfwTerminate();
    exit(1);
  }

  glfwMakeContextCurrent(window);
  glfwSwapInterval(0);

  if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
    fprintf(stderr, "Failed to initialize GLAD\n");
    exit(1);
  }
  glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glEnable(GL_DEPTH_TEST);
  return window;
}
