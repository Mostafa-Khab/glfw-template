/*********************************
 * author     : mostafa khaled
 * date       : Sat Sep 14 02:10:53 AM EEST 2024
 * desc       : 
 ********************************/
#ifndef SHADER_H
#define SHADER_H

#include <stdbool.h>

typedef struct shader
{
  unsigned int id;
} shader;

void shader_create(shader*, unsigned int type);
void shader_source(shader , const char* data);
void shader_compile(shader);

typedef struct program
{
  unsigned int id;
} program;

void program_create(program*);
void program_add_shader(program, shader);
void program_link(program);
void program_use(program);
unsigned int  program_uniform(program, const char* uname);
unsigned int  program_attrib (program, const char* aname);

void set_attrib(unsigned int location, int size, int offset, int stride);

#endif /* !SHADER_HPP */
