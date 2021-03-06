#include "ShadersManager.h"
#include <fstream>
#include <iostream>
#include <string>

ShadersManager::ShadersManager()
{
	
}

ShadersManager::~ShadersManager()
{
	//std::map<std::string, GLuint>::iterator t_iterator;
	for (auto t_iterator = c_programs.begin(); t_iterator != c_programs.end(); ++t_iterator)
		glDeleteProgram(t_iterator->second);
}

GLuint	ShadersManager::CreateProgram(std::string p_vertexShaderFile, std::string p_fragmentShaderFile, std::string p_programName)
{
	//compile both shaders
	GLuint t_compiledVertexShader   = CompileShader(p_vertexShaderFile, GL_VERTEX_SHADER);
	GLuint t_compiledFragmentShader = CompileShader(p_fragmentShaderFile, GL_FRAGMENT_SHADER);
	if (t_compiledFragmentShader == 0 || t_compiledVertexShader == 0)
		return 0;
	//create a program
	GLuint t_shaderProgram = glCreateProgram();
	//link the compiled shaders to a program
	glAttachShader(t_shaderProgram, t_compiledVertexShader);
	glAttachShader(t_shaderProgram, t_compiledFragmentShader);
	LinkProgram(&t_shaderProgram, t_compiledVertexShader, t_compiledFragmentShader);
	
	//store the program
	c_programs[p_programName] = t_shaderProgram;
	return t_shaderProgram;
}

GLuint	ShadersManager::GetProgram(std::string p_shaderName)
{
	return c_programs[p_shaderName];
}

GLuint	ShadersManager::CompileShader(std::string p_shaderFile, unsigned short p_shaderType)
{
	//read the shader from the specified file
	std::string t_shaderCode;
	std::ifstream t_shaderStream(p_shaderFile, std::ios::in);
	if (t_shaderStream.is_open()) {
		std::string Line = "";
		while (getline(t_shaderStream, Line))
			t_shaderCode += "\n" + Line;
		t_shaderStream.close();
	}
	else 
	{
		std::cout << "Impossible to open " << p_shaderFile << std::endl;
		return 0;
	}

	char const * t_shaderCodeConverted = t_shaderCode.c_str();
	GLuint r_shaderID = glCreateShader(p_shaderType);//create a empty shader of the passed type
	glShaderSource(r_shaderID, 1, &t_shaderCodeConverted, NULL);//set the source code to the created shader
	glCompileShader(r_shaderID);
	// Check for compile time errors
	GLint t_success;
	GLchar t_infoLog[512];
	glGetShaderiv(r_shaderID, GL_COMPILE_STATUS, &t_success);//set the shader to be queried and what to query about. Store the result code
	if (!t_success)
	{
		glGetShaderInfoLog(r_shaderID, 512, NULL, t_infoLog);//store the query info in t_infoLog
		std::cout << "ERROR COMPILING SHADER " << p_shaderFile << " COMPILATION_FAILED. INFO LOG: " << t_infoLog << std::endl;
		std::cin.get();
		return 0;
	}
	return r_shaderID;
}

void	ShadersManager::LinkProgram(GLuint* p_program, GLuint p_vertexShader, GLuint p_fragmentShader)
{
	glLinkProgram(*p_program);
	// Print linking errors if any
	GLint t_success;
	GLchar t_infoLog[512];
	glGetProgramiv(*p_program, GL_LINK_STATUS, &t_success);
	if (!t_success)
	{
		glGetProgramInfoLog(*p_program, 512, NULL, t_infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << t_infoLog << std::endl;
		std::cin.get();
	}

	// Delete the shaders as they're linked into our program now and no longer necessery
	glDeleteShader(p_vertexShader);
	glDeleteShader(p_fragmentShader);
}