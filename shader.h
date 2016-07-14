#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <GL/glew.h>

class Shader
{
public:
	Shader(const std::string & file_name);
	virtual ~Shader();
	void Bind();
private:
	static const unsigned int NUM_SHADERS = 2; // vertex + fragment = 2
	GLuint program;
	GLuint shaders[NUM_SHADERS];
};

#endif // SHADER_H
