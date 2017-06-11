#include "PerspectiveCamera.h"
#include "glm\gtc\matrix_transform.hpp"

//set fov in degrees.
PerspectiveCamera::PerspectiveCamera(float p_far, float p_near, float p_fov, float p_width, float p_height)
	: Camera(glm::perspective(glm::radians(p_fov), p_width / p_height, p_near, p_far))
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
