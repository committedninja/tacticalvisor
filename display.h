#ifndef DISPLAY_H
#define DISPLAY_H

#define GLEW_STATIC

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <string>

class Display {
public:
  Display(int width, int height, const std::string &title);
  virtual ~Display();
  void swapBuffers();
  void clear(float r, float g, float b, float a);

private:
  SDL_Window *window;
  SDL_GLContext context;
};

#endif // DISPLAY_H
