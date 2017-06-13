#include "OrthographicCamera.h"
#include "glm\gtc\matrix_transform.hpp"
#include <iostream>

OrthographicCamera::OrthographicCamera(float p_near, float p_far, float p_left, float p_right, float p_top, float p_bottom)
	: Camera(glm::ortho(p_left, p_right, p_bottom, p_top, p_near, p_far)),
	  c_near(p_near),
	  c_far(p_far),
	  c_left(p_left),
	  c_right(p_right),
	  c_top(p_top),
	  c_bottom(p_bottom)
{
}

OrthographicCamera::~OrthographicCamera()
{
}
void OrthographicCamera::BeginDraw()
{	 
}	 
	 
void OrthographicCamera::EndDraw()
{
}

void OrthographicCamera::DisplayEntityData(std::string p_tab)
{
	std::cout << p_tab << "Entity type: orthographic camera" << std::endl;
	std::cout << p_tab << "Far: " << c_far << " Near: " << c_near << " Right: " << c_right << " Left: " << c_left << " Top: " << c_top << " Bottom: " << c_bottom << std::endl;
}
