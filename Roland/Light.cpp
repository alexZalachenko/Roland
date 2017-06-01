#include "Light.h"

Light::Light()
	: IEntity(LightType), 
	  c_intensity(0,0,0),
	  c_isActive(false)
{
}

Light::~Light()
{
}

void Light::SeIntensity(Color p_color)
{
	c_intensity = p_color;
}

Color Light::GetIntensity()
{
	return c_intensity;
}

void Light::BeginDraw()
{
	//TODO
}

void Light::EndDraw()
{
	//TODO
}

bool Light::GetIsActive()
{
	return c_isActive;
}

void Light::SetIsActive(bool p_isActive)
{
	c_isActive = p_isActive;
}
