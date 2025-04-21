#include "window.h"
#include "camera.h"

extern struct camera cam;

static void framebufferSizeCallback(GLFWwindow* window, int width, int height){
  glViewport(0, 0, width, height);
}

static void mouseCallback(GLFWwindow *window, double x, double y){
  /* TODO:
   * - Also change the width and height of window resize
  */

  static float lastX;
  static float lastY;

  float offsetX = x - lastX;
  float offsetY = y - lastY;

  lastX = x;
  lastY = y;

  const float sens = 0.1f;
  offsetX *= sens;
  offsetY *= sens;

  cam.yaw += offsetX;
  cam.pitch -= offsetY;

  cam.camFront[0] = cos(glm_rad(cam.yaw)) * cos(glm_rad(cam.pitch));
  cam.camFront[1] = sin(glm_rad(cam.pitch));
  cam.camFront[2] = sin(glm_rad(cam.yaw)) * cos(glm_rad(cam.pitch));
  glm_normalize(cam.camFront);
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

  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
    fprintf(stderr, "Failed to initialize GLAD\n");
    exit(1);
  }

  glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
  glfwSetCursorPosCallback(window, mouseCallback);

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glEnable(GL_DEPTH_TEST);
  return window;
}
