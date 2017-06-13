#include "Light.h"
#include <iostream>

Light::Light()
	: IEntity(LightType), 
	  c_intensity(0,0,0),
	  c_isActive(false)
{
}

Light::Light(Color p_color)
	: IEntity(LightType), 
	  c_intensity(p_color),
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

void Light::DisplayEntityData(std::string p_tab)
{
	std::cout << p_tab << "Entity type: light	" << std::endl;
	std::cout << p_tab << "Color (RGB): " << c_intensity.c_red << " " << c_intensity.c_green << " " << c_intensity.c_blue << std::endl;
}
