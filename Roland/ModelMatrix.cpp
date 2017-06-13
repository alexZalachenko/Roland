#include "ModelMatrix.h"
#include <GLFW/glfw3.h>//for creating a window and reading users' input
#define GLEW_STATIC //use static binding. All the code used from the library is put into the executable and no needed to attach a dll
#include "glm\gtc\type_ptr.hpp"

ModelMatrix::ModelMatrix()
{
}

ModelMatrix::~ModelMatrix()
{
}

void ModelMatrix::ModelMatrixToShader()
{
	glm::mat4 t_modelMatrix = CalculateModelMatrix();
	glUniformMatrix4fv(c_matrixLocation, 1, GL_FALSE, glm::value_ptr(t_modelMatrix));
}

void ModelMatrix::PushMatrix(glm::mat4 p_matrix)
{
	c_transformations.push_back(p_matrix);
}

void ModelMatrix::PopMatrix()
{
	c_transformations.pop_back();
}

void ModelMatrix::Reset()
{
	c_transformations.clear();
	ModelMatrixToShader();
}

glm::mat4 ModelMatrix::CalculateModelMatrix()
{
	glm::mat4 t_modelMatrix;
	for (auto it = c_transformations.rbegin(); it != c_transformations.rend(); ++it)
		t_modelMatrix *= (*it);

	return t_modelMatrix;
}
