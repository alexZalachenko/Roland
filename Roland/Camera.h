#pragma once
#include "IEntity.h"
#include "glm\mat4x4.hpp"

class Camera : public IEntity
{
public:
	Camera();
	Camera(glm::mat4 p_projectionMatrix);
	~Camera();
	glm::mat4 GetProjectionMatrix()
	{
		return c_projectionMatrix;
	};

private:
	glm::mat4 c_projectionMatrix;
};

