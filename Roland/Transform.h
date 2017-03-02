#pragma once
#include "Entity.h"
#include "Matrix4x4.h"

class Transform : public Entity
{
public:
	Transform();
	~Transform();

private:
	Matrix4x4<double> c_matrix;

	void Identity();
	void LoadMatrix(Matrix4x4<double> p_matrix);
	void Transpose();
	void Translate(float p_x, float p_y, float p_z);
	void Rotate(float p_x, float p_y, float p_z, float p_w);
	void BeginDraw();
	void EndDraw();
};

