#include "Transform.h"
#include <glm\gtc\matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "ModelMatrix.h"
#include <iostream>

Transform::Transform(ModelMatrix* p_modelMatrix)
	:IEntity(TransformType),
	 c_matrix(),
	 c_modelMatrix(p_modelMatrix)
{
}

Transform::~Transform()
{
}

void Transform::SetIdentity()
{
	c_matrix = glm::mat4();//the default constructor creates a indentity matrix;
}

void Transform::DisplayEntityData(std::string p_tab)
{
	std::cout << p_tab << "Entity type: transform" << std::endl;
	std::cout << p_tab << "Transform matrix: "  << std::endl;
	std::cout << std::endl;
	for (size_t x = 0; x < c_matrix.length(); x++)
	{
		std::cout << p_tab;
		for (size_t y = 0; y < c_matrix[x].length(); y++)
		{
			std::cout << c_matrix[x][y] << " ";
		}
		if (x < c_matrix.length() - 1)
			std::cout << std::endl;
	}
	std::cout << std::endl;
	std::cout << std::endl;
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

//set rotation in degrees
void Transform::Rotate(float p_rotation, float p_rotationX, float p_rotationY, float p_rotationZ)
{
	c_matrix = glm::rotate(c_matrix, glm::radians(p_rotation), glm::vec3(p_rotationX, p_rotationY, p_rotationZ));
}

void Transform::Scale(float p_scaleX, float p_scaleY, float p_scaleZ)
{
	c_matrix = glm::scale(c_matrix, glm::vec3(p_scaleX, p_scaleY, p_scaleZ));
}

void Transform::BeginDraw()
{
	c_modelMatrix->PushMatrix(c_matrix);
}

void Transform::EndDraw()
{
	c_modelMatrix->PopMatrix();
}
