#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "texture.h"

GLuint loadImage(const char *path){
  int nrChannels, width, height;
  unsigned char *data;

  if((data = stbi_load(path, &width, &height, &nrChannels, 0)) == NULL){
    fprintf(stderr, "Error - Failed to load texture!\n");
    stbi_image_free(data);
    exit(5);
  }

  GLuint texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  stbi_image_free(data);
  return texture;
}
