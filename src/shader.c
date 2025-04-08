#include "shader.h"


/* Free memory after using the shader source */
const char *readShader(const char *path){
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


void shaderLog(GLuint shader){
  int success;
  char infoLog[512];

  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success){
    glGetShaderInfoLog(shader, 512, NULL, infoLog);
    printf("error, shader compilation failed\nshader id: %d\n%s\n", shader, infoLog);
  }
}

void programLog(GLuint program){
  int success;
  char infoLog[512];

  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if(!success){
    glGetProgramInfoLog(program, 512, NULL, infoLog);
    printf("error, shader program linking failed\nprogram id: %d\n%s\n", program, infoLog);
  }
}
