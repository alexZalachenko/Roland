#pragma once
#include <map>
#define GLEW_STATIC //use static binding. All the code used from the library is put into the executable and no needed to attach a dll
#include <GL/glew.h>//for abstracting cumbersome OpenGL procedures

class ShadersManager
{
public:
	ShadersManager();
	~ShadersManager();
	
	GLuint CreateProgram(std::string p_vertexShaderFile, std::string p_fragmentShaderFile, std::string p_programName);
	GLuint GetProgram(std::string p_shaderName);
	GLuint GetActiveProgram()
	{
		return c_activeProgram;
	}
	void	UseProgram(GLuint p_program)
	{
		glUseProgram(p_program);
		c_activeProgram = p_program;
	}

private:
	GLuint CompileShader(std::string p_shaderFile, unsigned short p_shaderType);
	void LinkProgram(GLuint* p_program, GLuint p_vertexShader, GLuint p_fragmentShader);
	std::map<std::string, GLuint> c_programs;
	GLuint c_activeProgram;
};

