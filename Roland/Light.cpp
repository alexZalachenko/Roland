#include "Light.h"
#include <iostream>


Light::Light()
	: IEntity(LightType), 
	  c_color(1,1,1)
{
}

Light::Light(glm::vec3 p_color)
	: IEntity(LightType), 
	  c_color(p_color)
{
}

Light::~Light()
{
}

glm::vec3 Light::GetColor()
{
	return c_color;
}

void Light::BeginDraw()
{
	//TODO
}

void Light::EndDraw()
{
	//TODO
}

void Light::DisplayEntityData(std::string p_tab)
{
	std::cout << p_tab << "Entity type: light	" << std::endl;
	std::cout << p_tab << "Color (RGB): " << c_color.r << " " << c_color.g << " " << c_color.b << std::endl << std::endl;
}

void Light::SetColor(glm::vec3 p_newColor)
{
	c_color.r = NormalizeValue(p_newColor.r);
	c_color.g = NormalizeValue(p_newColor.g);
	c_color.b = NormalizeValue(p_newColor.b);
}

float Light::NormalizeValue(float p_value)
{
	if (p_value < 0)
		p_value = 0;
	else if (p_value > 255)
		p_value = 255;
	return p_value;
}
