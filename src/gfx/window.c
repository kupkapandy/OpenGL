#include "window.h"
#include "render.h"

static inline void windowSizeCallBack(GLFWwindow* window, int width, int height) {
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

  printf("%f %f %f\n", renderer.cam.camPos[0], renderer.cam.camPos[1], renderer.cam.camPos[2]);

}

void createWindow(void) {
  if(!glfwInit()) {
    fprintf(stderr, "GLFW failed to initialize!");
    exit(1);
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  if((window.window = glfwCreateWindow(WIDTH, HEIGHT, "Learn OpenGL", NULL, NULL)) == NULL) {
    fprintf(stderr, "Failed to create GLFW window\n");
    glfwTerminate();
    exit(1);
  }

  glfwMakeContextCurrent(window.window);
  glfwSwapInterval(0);

  if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    fprintf(stderr, "Failed to initialize GLAD\n");
    glfwTerminate();
    exit(1);
  }

  glfwSetInputMode(window.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glfwSetFramebufferSizeCallback(window.window, windowSizeCallBack);
  glfwSetCursorPosCallback(window.window, mouseCallback);

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glEnable(GL_DEPTH_TEST);
}
