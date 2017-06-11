#include "Camera.h"

Camera::Camera(glm::mat4 p_projectionMatrix)
	: IEntity(CameraType), 
	  c_projectionMatrix(p_projectionMatrix)
{
}

Camera::~Camera()
{
}

