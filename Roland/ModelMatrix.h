#pragma once
#include "glm\mat4x4.hpp"
#include <list>
#include <GL/glew.h>//for abstracting cumbersome OpenGL procedures

class ModelMatrix
{

public:
	ModelMatrix();
	~ModelMatrix();
	void ModelMatrixToShader();
	void PushMatrix(glm::mat4 p_matrix);
	void PopMatrix();
	void Reset();
	void SetActiveProgram(GLuint p_activeProgram)
	{
		c_activeProgram = p_activeProgram;
	}

private:
	std::list<glm::mat4> c_transformations;
	GLuint c_activeProgram;
	glm::mat4 CalculateModelMatrix();
};

