#include <glad/glad.h>
#include "log.h"
#include "buffer.h"

void buffer_create(buffer* b)
{
  glGenBuffers(1, &b->id);
  if(!b->id)
    log("failed to create requested buffer");
}

void buffer_bind(buffer b, unsigned int target)
{
  glBindBuffer(target, b.id);
}

void buffer_data(buffer b, unsigned int target, unsigned int size, const void* data, unsigned int usage)
{
   glBufferData(target, size, data, usage);
}

void buffer_delete(buffer* b)
{
  glDeleteBuffers(1, &b->id);
}

void buffer_draw_arrays(buffer b, unsigned int mod, unsigned int first, unsigned int count)
{
  glBindBuffer(GL_ARRAY_BUFFER, b.id);
  glDrawArrays(mod, first, count);
}
