#include "Transform.h"
#include <glm\gtc\matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Transform::Transform()
	:c_matrix()
{
}

Transform::~Transform()
{
}

void Transform::SetIdentity()
{
	c_matrix[0][0] = 1;
	c_matrix[1][1] = 1;
	c_matrix[2][2] = 1;
	c_matrix[3][3] = 1;
}
	 
void Transform::LoadMatrix(glm::mat4 p_matrix)
{
	c_matrix = p_matrix;
}

void Transform::Transpose()
{
	c_matrix = glm::transpose(c_matrix);
}
	
void Transform::Translate(float p_translationX, float p_translationY, float p_translationZ)
{
	c_matrix = glm::translate(c_matrix, glm::vec3(p_translationX, p_translationY, p_translationZ));
}

void Transform::Rotate(float p_rotation, float p_rotationX, float p_rotationY, float p_rotationZ)
{
	c_matrix = glm::rotate(c_matrix, p_rotation, glm::vec3(p_rotationX, p_rotationY, p_rotationZ));
}

void Transform::Scale(float p_scaleX, float p_scaleY, float p_scaleZ)
{
	c_matrix = glm::scale(c_matrix, glm::vec3(p_scaleX, p_scaleY, p_scaleZ));
}

void Transform::BeginDraw()
{
	//TODO

	//apilar matriz actual
	//multiplicar la matriz de la transformacion a la matriz actual
}

void Transform::EndDraw()
{
	//TODO
	//desapilar matriz y ponerla como actual
}
