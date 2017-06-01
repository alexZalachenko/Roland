#include "OrthographicCamera.h"
#include "glm\gtc\matrix_transform.hpp"

OrthographicCamera::OrthographicCamera()
{
}

OrthographicCamera::OrthographicCamera(float p_near, float p_far, float p_left, float p_right, float p_top, float p_bottom)
	: Camera(glm::ortho(p_left, p_right, p_bottom, p_top, p_near, p_far))
{
}

OrthographicCamera::~OrthographicCamera()
{
}