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

  if((window = glfwCreateWindow(800, 600, "Learn OpenGL", NULL, NULL)) == NULL){
    fprintf(stderr, "Failed to create GLFW window\n");
    glfwTerminate();
    exit(1);
  }

  glfwMakeContextCurrent(window);

  if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
    fprintf(stderr, "Failed to initialize GLAD\n");
    exit(1);
  }
  glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
  return window;
}
