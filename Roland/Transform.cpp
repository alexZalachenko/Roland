#include "Transform.h"

Transform::Transform()
	:c_matrix()
{
}

Transform::~Transform()
{
}

void Transform::Identity()
{
	c_matrix.SetIdentity();
}
	 
void Transform::LoadMatrix(Matrix4x4<double> p_matrix)
{
	c_matrix = p_matrix;
}

void Transform::Transpose()
{
	//TODO
}
	
void Transform::Translate(float p_x, float p_y, float p_z)
{
	//TODO
}

void Transform::Rotate(float p_x, float p_y, float p_z, float p_w)
{
	//TODO
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
