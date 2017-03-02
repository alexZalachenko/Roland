#include "Camera.h"

//TODO

Camera::Camera()
	:c_isActive(false)
{
}

Camera::~Camera()
{
}

void Camera::SetPerspective(float a, float b)
{

}

void Camera::SetParallel(float a, float b)
{
}

void Camera::BeginDraw()
{

}

void Camera::EndDraw()
{

}

bool Camera::GetIsActive()
{
	return c_isActive;
}

void Camera::SetIsActive(bool p_isActive)
{
	c_isActive = p_isActive;
}
