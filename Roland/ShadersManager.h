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

private:
	GLuint CompileShader(std::string p_shaderFile, unsigned short p_shaderType);
	void LinkShader(GLuint* p_program, GLuint p_shader);
	std::map<std::string, GLuint> c_programs;
};

