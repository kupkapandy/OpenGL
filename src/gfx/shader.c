#include "shader.h"

static const char *readShader(const char *path){
  FILE *fp;
  if((fp = fopen(path, "r")) == NULL){
    fprintf(stderr, "ERROR: WRONG PATH TO SHADER FILE!\nGiven path: %s", path);
    exit(1);
  }

  fseek(fp, 0, SEEK_END);
  uint32_t fileSize = ftell(fp);
  fseek(fp, 0, SEEK_SET);

  char *p;
  if((p = (char *)malloc(fileSize + 1)) == NULL){
    fprintf(stderr, "ERROR: MALLOC FAILED WHILE ALLOCATING STRING FOR SHADER!\n");
    exit(1);
  }

  if((fread(p, 1, fileSize, fp)) == 0){
    fprintf(stderr, "ERROR: FREAD FAILED WHILE COPYING FROM SHADER FILE\n");
    exit(1);
  }

  p[fileSize] = '\0';
  return p;
}

static void shaderLog(GLuint shader){
  int success;
  char infoLog[512];

  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success){
    glGetShaderInfoLog(shader, 512, NULL, infoLog);
    printf("error, shader compilation failed\nshader id: %d\n%s\n", shader, infoLog);
  }
}

static void programLog(GLuint program){
  int success;
  char infoLog[512];

  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if(!success){
    glGetProgramInfoLog(program, 512, NULL, infoLog);
    printf("error, shader program linking failed\nprogram id: %d\n%s\n", program, infoLog);
  }
}

GLuint createShader(GLenum type, const char *path){
  const char *shaderSource = readShader(path);

  GLuint shader = glCreateShader(type);
  glShaderSource(shader, 1, &shaderSource, NULL);
  glCompileShader(shader);

  shaderLog(shader);

  free((void *)shaderSource);
  return shader;
}

void createProgram(GLuint *shaderProgram, GLuint cnt, ...){
  va_list va_ptr;
  va_start(va_ptr, cnt);

  *shaderProgram = glCreateProgram();
  for(GLuint i = 0; i < cnt; ++i){
    GLuint shader = va_arg(va_ptr, GLuint);
    glAttachShader(*shaderProgram, shader);
    glDeleteShader(shader);
  }

  glLinkProgram(*shaderProgram);
  programLog(*shaderProgram);

  va_end(va_ptr);
}

void deleteProgram(GLuint shaderProgram){
  glDeleteProgram(shaderProgram);
}
