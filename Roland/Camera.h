#pragma once
#include "IEntity.h"
#include "glm\mat4x4.hpp"

class Camera : public IEntity
{
public:
	Camera(glm::mat4 p_projectionMatrix);
	virtual ~Camera();
	glm::mat4 GetProjectionMatrix()
	{
		return c_projectionMatrix;
	};
	virtual glm::mat4 GetViewMatrix()
	{
		return glm::mat4();
	}

protected:
	glm::mat4 c_projectionMatrix;
};

