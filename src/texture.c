#include <glad/glad.h>

#include "log.h"
#include "texture.h"

void texture_create(texture* t)
{
  glGenTextures(1, &t->id);
  if(!t->id)
    log("failed to create requested texture");
}

void texture_bind(texture t)
{
  glBindTexture(GL_TEXTURE_2D, t.id);
}

//texture is unused here
void texture_data(texture t, int width, int height, int comps, const unsigned char* data)
{
  unsigned int f = (comps == 4)? GL_RGBA : (comps == 3)? GL_RGB : GL_RED;
  glTexImage2D(GL_TEXTURE_2D, 0, f, width, height, 0, f, GL_UNSIGNED_BYTE, data);
}

void texture_filters(texture t, int wrap, int min_mag)
{
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);

  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, min_mag);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_mag);
}

void texture_delete(texture* t)
{
  glDeleteTextures(1, &t->id);
}
