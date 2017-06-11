#include "FPSCamera.h"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtx\rotate_vector.hpp"
#include <GLFW/glfw3.h>//for creating a window and reading users' input

FPSCamera::FPSCamera(float p_far, float p_near, float p_fov, float p_width, float p_height, float p_startingMouseX, float p_startingMouseY)
	:PerspectiveCamera(p_far, p_near, p_fov, p_width, p_height)
{
	c_lastMousePositionX = p_startingMouseX;
	c_lastMousePositionY = p_startingMouseY;
	c_position = glm::vec3(0, 0, 0);
}

FPSCamera::~FPSCamera()
{
}

glm::mat4 FPSCamera::GetViewMatrix()
{
	//yaw
	glm::vec3 t_direction	= glm::rotate(glm::vec3(0, 0, -1),	c_yaw,		glm::vec3(0, 1, 0));
	glm::vec3 t_right		= glm::rotate(glm::vec3(1, 0, 0),	c_yaw,		glm::vec3(0, 1, 0));
	//pitch
	t_direction				= glm::rotate(t_direction,			c_pitch,	t_right);
	glm::vec3 t_up			= glm::rotate(glm::vec3(0, 1, 0),	c_pitch,	t_right);
	return glm::lookAt(c_position, (t_direction + c_position), t_up);
}

void FPSCamera::ReceiveKeyboardInput(int p_key, int p_action)
{
	if (p_action == GLFW_PRESS || p_action == GLFW_REPEAT)
	{
		switch (p_key)
		{
		case GLFW_KEY_W:
			c_position += glm::vec3(-glm::sin(c_yaw), 0, -glm::cos(c_yaw)) * c_movementSpeed;
			break;
		case GLFW_KEY_A:
			c_position += glm::vec3(-glm::cos(c_yaw), 0, glm::sin(c_yaw)) * c_movementSpeed;
			break;
		case GLFW_KEY_S:
			c_position += glm::vec3( glm::sin(c_yaw), 0,  glm::cos(c_yaw)) * c_movementSpeed;
			break;
		case GLFW_KEY_D:
			c_position += glm::vec3( glm::cos(c_yaw), 0,  -glm::sin(c_yaw)) * c_movementSpeed;
			break;
		}
	}
}

void FPSCamera::ReceiveMouseMovementInput(double p_newPositionX, double p_newPositionY)
{
	c_yaw	+= (c_lastMousePositionX - p_newPositionX) * c_rotationSpeed;
	c_pitch += (c_lastMousePositionY - p_newPositionY) * c_rotationSpeed;
	c_lastMousePositionX = p_newPositionX;
	c_lastMousePositionY = p_newPositionY;
}