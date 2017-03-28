#pragma once
#include "IEntity.h"
#include "Matrix4x4.h"

class Transform : public IEntity
{
public:
	Transform();
	~Transform();

private:
	Matrix4x4<double> c_matrix;

	void IdIEntity();
	void LoadMatrix(Matrix4x4<double> p_matrix);
	void Transpose();
	void Translate(float p_x, float p_y, float p_z);
	void Rotate(float p_x, float p_y, float p_z, float p_w);
	void BeginDraw();
	void EndDraw();
};

