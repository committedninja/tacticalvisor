#include "shader.h"
#include <iostream>
#include <fstream>

static GLuint CreateShader(const std::string & content, GLenum shaderType);
static void checkShaderError(GLuint shader, GLuint flag, bool is_program, const std::string & error_messagee);
static std::string LoadShader(const std::string & file_name);

Shader::Shader(const std::string & file_name)
{
	program = glCreateProgram();
	shaders[0] = CreateShader(LoadShader(file_name + ".vsh"), GL_VERTEX_SHADER);
	shaders[1] = CreateShader(LoadShader(file_name + ".frag"), GL_FRAGMENT_SHADER);

	for(unsigned int i = 0; i < NUM_SHADERS; i++) glAttachShader(program, shaders[i]);

	glBindAttribLocation(program, 0, "position"); // what part of the data to read as what variable

	glLinkProgram(program);
	checkShaderError(program, GL_LINK_STATUS, true, "Shader program linking failed");
	glValidateProgram(program);
	checkShaderError(program, GL_VALIDATE_STATUS, true, "Shader program is invalid");
}
Shader::~Shader()
{
	for(unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glDetachShader(program, shaders[i]);
		glDeleteShader(shaders[i]);
	}
	glDeleteProgram(program);
}
void Shader::Bind()
{
	glUseProgram(program);
}
static GLuint CreateShader(const std::string & content, GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);
	if(shader == 0) // not enough memory
		std::cerr << "Error: Shader creation failed." << std::endl;
	const GLint shader_source_strings_lengths[1] = { content.length() };
	const GLchar * shader_source_strings[1];
	shader_source_strings[0] = content.c_str();

	glShaderSource(shader, 1, shader_source_strings, shader_source_strings_lengths);
	glCompileShader(shader);
	checkShaderError(shader, GL_COMPILE_STATUS, false, "Shader compilation error");
	return shader;
}

static void checkShaderError(GLuint shader, GLuint flag, bool is_program, const std::string & error_message)
{
	GLint success = 0;
	GLchar error[1024] = {0};
	if(is_program)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if(success == GL_FALSE)
	{
		if(is_program)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		std::cerr << error_message << ": '" << error << "'" << std::endl;
	}
}
static std::string LoadShader(const std::string & file_name)
{
	std::ifstream file;
	file.open((file_name).c_str());

	std::string output;
	std::string line;
	if(file.is_open())
	{
		while(file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	} else {
		std::cerr << "Unable to load shader: " << file_name << std::endl;
	}
	return output;
}
