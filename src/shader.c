#include <glad/glad.h>

#include <stdio.h>

#include "log.h"
#include "shader.h"

#define ERROR_BUFFER_SIZE

char shader_ebuff[ERROR_BUFFER_SIZE] = {0};

void shader_create(shader* s, unsigned int type)
{
  s->id = glCreateShader(type);
  if(!s->id)
    log("failed to create shader");
}

void shader_compile(shader s)
{
  glCompileShader(s.id);

  int status = 0;
  glGetShaderiv(s.id, GL_COMPILE_STATUS, &status);

  if(status == GL_FALSE)
  {
     int logsize = 0;
     glGetShaderiv(s.id, GL_INFO_LOG_LENGTH, &logsize);
     glGetShaderInfoLog(s.id, logsize, &logsize, shader_ebuff);
     log(shader_ebuff);
  }
}

void shader_source(shader s, const char* data)
{
  glShaderSource(s.id, 1, &data, NULL);
}

void program_create(program* p)
{
  p->id = glCreateProgram();
  if(!p->id)
    log("failed to create shader program");
}

void program_add_shader(program p, shader s)
{
  glAttachShader(p.id, s.id);
}

void program_link(program p)
{
  glLinkProgram(p.id);
}

void program_use(program p)
{
  glUseProgram(p.id);
}

unsigned int program_uniform(program p, const char* uname)
{
  return glGetUniformLocation(p.id, uname);
}

unsigned int program_attrib(program p, const char* aname)
{
  return glGetAttribLocation(p.id, aname);
}

void set_attrib(unsigned int location, int size, int offset, int stride)
{
  glEnableVertexAttribArray(location);
  glVertexAttribPointer(location, size, GL_FLOAT, GL_FALSE, stride, (void*)(offset * sizeof(float)));
}
