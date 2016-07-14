#ifndef DISPLAY_H
#define DISPLAY_H

#define GLEW_STATIC

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <string>
#include <iostream>

class Display
{
	public:
		Display(int width, int height, const std::string & title);
		virtual ~Display();
		void swapBuffers();
		void clear(float r, float g, float b, float a);
	private:
		SDL_Window * window;
		SDL_GLContext context;
};

#endif // DISPLAY_H
