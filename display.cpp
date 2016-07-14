#include "display.h"

Display::Display(int width, int height, const std::string & title)
{
	SDL_Init(SDL_INIT_VIDEO);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8); // how many bits for red
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8); // how many bits for green
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8); // how many bits for blue
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8); // how many bits for opacity
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32); // total of above ^

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // enable double buffering
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);


	window  = SDL_CreateWindow(title.c_str(), 0 /* SDL_WINDOWPOS_CENTERED */, 0 /* SDL_WINDOWPOS_UNDEFINED */, width, height, SDL_WINDOW_OPENGL /* SDL_WINDOW_FULLSCREEN */);
	context = SDL_GL_CreateContext(window);

	glewExperimental = GL_TRUE;
	GLenum status = glewInit();
	if(status != GLEW_OK)
	{
		std::cerr << "GLEW failed to initialize" << std::endl;
	}

}
Display::~Display()
{
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
}
void Display::swapBuffers()
{
	SDL_GL_SwapWindow(window);
}
void Display::clear(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT);
}
