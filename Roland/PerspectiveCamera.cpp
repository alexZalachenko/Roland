#include "PerspectiveCamera.h"
#include "glm\gtc\matrix_transform.hpp"
#include <iostream>

//set fov in degrees.
PerspectiveCamera::PerspectiveCamera(float p_far, float p_near, float p_fov, float p_width, float p_height)
	: Camera(glm::perspective(glm::radians(p_fov), p_width / p_height, p_near, p_far)),
	  c_far(p_far),
	  c_near(p_near),
	  c_fov(p_fov),
	  c_width(p_width),
	  c_height(p_height)
{
}

PerspectiveCamera::~PerspectiveCamera()
{
}

void PerspectiveCamera::BeginDraw()
{
}

void PerspectiveCamera::EndDraw()
{
}

void PerspectiveCamera::DisplayEntityData(std::string p_tab)
{
	std::cout << p_tab << "Entity type: Perspective camera" << std::endl;
	std::cout << p_tab << "Far: " << c_far << " Near: " << c_near << " FOV: " << c_fov << " Width: " << c_width << " Height: " << c_height << std::endl;
}
