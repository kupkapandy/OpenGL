#include "window.h"
#include "../body/render.h"

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

  renderer.cam.yaw += offsetX;
  renderer.cam.pitch -= offsetY;

  if(renderer.cam.pitch > 89.0f)
    renderer.cam.pitch = 89.0f;
  if(renderer.cam.pitch < -89.0f)
    renderer.cam.pitch = -89.0f;

  renderer.cam.camFront[0] = cos(glm_rad(renderer.cam.yaw)) * cos(glm_rad(renderer.cam.pitch));
  renderer.cam.camFront[1] = sin(glm_rad(renderer.cam.pitch));
  renderer.cam.camFront[2] = sin(glm_rad(renderer.cam.yaw)) * cos(glm_rad(renderer.cam.pitch));
  glm_normalize(renderer.cam.camFront);
}

void initWindow(void){
  global.window.width = WIDTH;
  global.window.height = HEIGHT;
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  if((global.window.window = glfwCreateWindow(global.window.width, global.window.height, "Learn OpenGL", NULL, NULL)) == NULL){
    fprintf(stderr, "Failed to create GLFW window\n");
    glfwTerminate();
    exit(1);
  }

  glfwMakeContextCurrent(global.window.window);
  glfwSwapInterval(0);

  glfwSetInputMode(global.window.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
    fprintf(stderr, "Failed to initialize GLAD\n");
    exit(1);
  }

  glfwSetFramebufferSizeCallback(global.window.window, framebufferSizeCallback);
  glfwSetCursorPosCallback(global.window.window, mouseCallback);

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glEnable(GL_DEPTH_TEST);
}
