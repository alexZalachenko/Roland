#pragma once
#include <GLFW/glfw3.h>//for creating a window and reading users' input
#include "InputHandler.h"

namespace OpenGLCallbacks
{
	float c_halfWidth, c_halfHeight;
	void HandleKeyboardInput(GLFWwindow* p_window, int p_key, int p_scancode, int p_action, int p_mode)
	{
		InputHandler::Instance()->HandleKeyboardInput(p_key, p_action);
		if (p_key == GLFW_KEY_ESCAPE && p_action == GLFW_PRESS)
			glfwSetWindowShouldClose(p_window, GL_TRUE);
	}

	void HandleMouseMovementInput(GLFWwindow* p_window, double p_newPositionX, double p_newPositionY)
	{
		InputHandler::Instance()->HandleMouseMovementInput(p_newPositionX, p_newPositionY);
	}
}