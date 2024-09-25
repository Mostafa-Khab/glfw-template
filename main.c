#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include </sasa/glfw-src/deps/linmath.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "src/log.h"
#include "src/shader.h"
#include "src/texture.h"
#include "src/buffer.h"

typedef struct Vertex
{
  vec2 pos;
  vec3 color;
  vec2 tex;
} Vertex;

Vertex verts1[] =
{
    { -0.1f,-0.1f, 1.f, 1.f, 1.f, 0.0, 0.0 },
    { -0.3f,-0.1f, 1.f, 1.f, 1.f, 0.5, 0.0 },
    { -0.1f,-0.3f, 1.f, 1.f, 1.f, 0.0, 1.0 },
    { -0.3f,-0.3f, 1.f, 1.f, 1.f, 0.5, 1.0 },
};

Vertex verts2[] =
{
    { 0.1f,0.1f, 1.f, 1.f, 1.f, 0.0, 0.0 },
    { 0.3f,0.1f, 1.f, 1.f, 1.f, 0.5, 0.0 },
    { 0.1f,0.3f, 1.f, 1.f, 1.f, 0.0, 1.0 },
    { 0.3f,0.3f, 1.f, 1.f, 1.f, 0.5, 1.0 },
};

const char* vshader_source = 
"#version 110\n"
"uniform mat4 M;\n"
"uniform mat4 P;\n"
"attribute vec2 vPos;\n"
"attribute vec3 vCol;\n"
"attribute vec2 vTex;\n"
"varying vec3 color;\n"
"varying vec2 texCoord;\n"
"void main() {\n"
"gl_Position = M * vec4(vPos, 1.0, 1.0) * P;\n"
"color = vCol;\n"
"texCoord = vTex;\n"
"}";

const char* fshader_source = 
"#version 110\n"
"uniform sampler2D tex0;\n"
"varying vec3 color;\n"
"varying vec2 texCoord;\n"
"void main() {\n"
"gl_FragColor = texture2D(tex0, texCoord) * vec4(color, 1.0);\n"
"}\n"
;

void keycallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

const char* glGetErrorString(GLenum error)
{
  switch(error)
  {
    case GL_NO_ERROR:          return "no error";
    case GL_INVALID_ENUM:      return "invalid enum";
    case GL_INVALID_VALUE:     return "invalid value";
    case GL_INVALID_OPERATION: return "invalid operation";
    //case GL_INVALID_FRAMEBUFFER_OPERATION: "
    case GL_OUT_OF_MEMORY:     return "out of memory";
    //case GL_STACK_UNDERFLOW:
    //case GL_STACK_OVERFLOW:
    //case GL_CONTEXT_LOST:
    default:                   return "Unknown Error";
  }
}

void _glCheckErrors(const char* file, int line)
{
#ifndef DEBUG
  return;
#endif

  GLenum err;
  while((err = glGetError()) != GL_NO_ERROR)
    fprintf(stderr, "\033[31mOpenGl Error[%s:%d](%u): %s\033[0m\n",
            file, line, err, glGetErrorString(err));
}

#define glCheckErrors() _glCheckErrors(__FILE__, __LINE__)

#define glCall(X) X; glCheckErrors();

int main(int argc, const char* argv[])
{
  int width  = argc > 3? atoi(argv[1]) : 700;
  int height = argc > 3? atoi(argv[2]) : 700;

  if(!glfwInit())
  {
    log("failed to init glfw");
    return -1;
  }

  glfwWindowHint(GLFW_VERSION_MAJOR, 2);
  glfwWindowHint(GLFW_VERSION_MINOR, 1);
  GLFWwindow* window = glfwCreateWindow(width, height, "gfx-test", 0, NULL);

  if(!window)
  {
    glfwTerminate();
    log("failed to create glfw window");
    return -1;
  }
  glfwMakeContextCurrent(window);

  if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    glfwTerminate();
    log("failed to initialize glad");
    return -1;
  }

  glfwSetKeyCallback(window, keycallback);

  shader vshader;
  shader_create(&vshader, GL_VERTEX_SHADER);
  shader_source(vshader, vshader_source);
  shader_compile(vshader);

  shader fshader;
  shader_create(&fshader, GL_FRAGMENT_SHADER);
  shader_source(fshader, fshader_source);
  shader_compile(fshader);

  program sprogram;
  program_create(&sprogram);
  program_add_shader(sprogram, vshader);
  program_add_shader(sprogram, fshader);
  program_link(sprogram);

  int m_location  = program_uniform(sprogram, "M");
  int p_location  = program_uniform(sprogram, "P");
  int vpos_location = program_attrib(sprogram, "vPos");
  int vcol_location = program_attrib(sprogram, "vCol");
  int vtex_location = program_attrib(sprogram, "vTex");

  buffer buff1;
  buffer_create(&buff1);
  buffer_bind(buff1, GL_ARRAY_BUFFER);
  buffer_data(buff1, GL_ARRAY_BUFFER, sizeof(verts1), verts1, GL_STATIC_DRAW);

  set_attrib(vpos_location, 2, 0, sizeof(Vertex));
  set_attrib(vcol_location, 3, 2, sizeof(Vertex));
  set_attrib(vtex_location, 2, 5, sizeof(Vertex));

  buffer buff2;
  buffer_create(&buff2);
  buffer_bind(buff2, GL_ARRAY_BUFFER);
  buffer_data(buff2, GL_ARRAY_BUFFER, sizeof(verts2), verts2, GL_STATIC_DRAW);

  set_attrib(vpos_location, 2, 0, sizeof(Vertex));
  set_attrib(vcol_location, 3, 2, sizeof(Vertex));
  set_attrib(vtex_location, 2, 5, sizeof(Vertex));

  int imgw, imgh, imgc;
  unsigned char* imgdata = stbi_load("assets/bird64.png", &imgw, &imgh, &imgc, 0);
  if(!imgdata)
  {
    log("failed to load requested image");
    glfwTerminate();
    return -1;
  }

  printf("loading img: %dx%d with %d components", imgw, imgh, imgc);

  texture tex;
  texture_create(&tex);
  texture_bind(tex);
  texture_data(tex, imgw, imgh, imgc, imgdata);
  texture_filters(tex, GL_REPEAT, GL_NEAREST);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glBlendEquation(GL_FUNC_ADD);

  mat4x4 m, p;
  while(!glfwWindowShouldClose(window))
  {
    glfwGetFramebufferSize(window, &width, &height);
    float ratio = (float)width / height;

    mat4x4_ortho(p, -ratio, ratio, -1, 1, 1, -1);

    glCall(glViewport(0, 0, width, height);)
    glCall(glClear(GL_COLOR_BUFFER_BIT);)

    program_use(sprogram);
    glCall(glUniformMatrix4fv(p_location, 1,GL_FALSE, (float*)&p);)

    texture_bind(tex);

    {
      mat4x4_identity(m);
      mat4x4_rotate_Z(m, m, (float)glfwGetTime());
      glCall(glUniformMatrix4fv(m_location, 1,GL_FALSE, (float*)&m);)

      buffer_draw_arrays(buff1, GL_TRIANGLE_STRIP, 0, 4);
      set_attrib(vpos_location, 2, 0, sizeof(Vertex));
      set_attrib(vcol_location, 3, 2, sizeof(Vertex));
      set_attrib(vtex_location, 2, 5, sizeof(Vertex));
    }

    {
      mat4x4_identity(m);
      mat4x4_rotate_Z(m, m, (float)glfwGetTime());
      glCall(glUniformMatrix4fv(m_location, 1,GL_FALSE, (float*)&m);)

      buffer_draw_arrays(buff2, GL_TRIANGLE_STRIP, 0, 4);
      set_attrib(vpos_location, 2, 0, sizeof(Vertex));
      set_attrib(vcol_location, 3, 2, sizeof(Vertex));
      set_attrib(vtex_location, 2, 5, sizeof(Vertex));
    }
    
    glfwPollEvents();
    glfwSwapBuffers(window);
  }

  buffer_delete(&buff1);
  buffer_delete(&buff2);
  texture_delete(&tex);

  glfwTerminate();
  stbi_image_free(imgdata);
  return 0;
}
