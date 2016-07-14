#include "display.h"
#include "shader.h"
#include <SDL2/SDL.h>
#include <iostream>

int main(int argc, char **argv) {
  /* VERY TEMPORARY */
  /*const GLchar* vertexSource =
          "#version 150 core\n"
          "in vec2 position;"
          "in vec3 color;"
          "out vec3 Color;"
          "void main() {"
          "   Color = color;"
          "   gl_Position = vec4(position, 0.0, 1.0);"
          "}";

  const GLchar* fragmentSource =
          "#version 150 core\n"
          "in vec3 Color;"
          "out vec4 outColor;"
          "void main() {"
          "   	outColor = vec4(0.5, 0.0, 0.0, 1.0);"
          "}";
    INDEED        */

  Display display(800, 600, "OpenGL Testing Zone");
  std::cout << "OpenGL Testing Zone initiating........................"
            << std::endl;
  SDL_Init(SDL_INIT_TIMER);
  SDL_Init(SDL_INIT_EVENTS);

  float vertices[] = {
      0.0f,  0.5f,  0.0f, // Vertex 1 (x,y,z)
      0.5f,  -0.5f, 0.0f, // Vertex 2 (x,y,z)
      -0.5f, -0.5f, 0.0f  // Vertex 3 (x,y,z)
  };

  GLuint vertexBuffer;
  glGenBuffers(1, &vertexBuffer); // generate 1 buffer, the GLuint is like a
                                  // pointer type for openGL
  glBindBuffer(
      GL_ARRAY_BUFFER,
      vertexBuffer); // bind type array buffer to the pointer "vertexBuffer"
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,
               GL_STATIC_DRAW); // put the data (of the vertices to draw) in the
                                // active object (which I binded to vertexBuffer
                                // in the previous line)

  Shader shader("../OpenGL_Playground/2dshader");
  SDL_Event windowEvent;
  SDL_PollEvent(&windowEvent);
  display.clear(0.0f, 0.15f, 0.3f, 1.0f);
  while (windowEvent.type != SDL_QUIT) {
    switch (windowEvent.type) {
    default:
      std::cerr << "Unhandled event type: " + windowEvent.type << std::endl;
    }
    std::cout << "hi" << std::endl;
    // display.clear();
    display.swapBuffers(); // swap front and back buffer
    SDL_PollEvent(&windowEvent);
  }
  SDL_Quit();
  return 0;
}
