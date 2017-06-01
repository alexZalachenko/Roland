#pragma once
#include "IEntity.h"
#include <glm\glm.hpp>	
class ModelMatrix;

class Transform : public IEntity
{
public:
	Transform(ModelMatrix* p_modelMatrix);
	~Transform();
	glm::mat4 GetMatrix()
	{
		return c_matrix;
	};
	void Translate(float p_translationX, float p_translationY, float p_translationZ);
	void Rotate(float p_rotation, float p_rotationX, float p_rotationY, float p_rotationZ);
	void Scale(float p_scaleX, float p_scaleY, float p_scaleZ);
	void SetIdentity();

private:
	glm::mat4 c_matrix;
	ModelMatrix* c_modelMatrix;
	void LoadMatrix(glm::mat4 p_matrix);
	void Transpose();
	
	void BeginDraw();
	void EndDraw();
};

