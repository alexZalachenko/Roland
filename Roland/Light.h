#pragma once
#include "IEntity.h"
#include <string>
#include "glm\vec3.hpp"

class Light : public IEntity
{
public:
	Light();
	Light(glm::vec3 p_color);
	~Light();
	glm::vec3	GetColor();
	void		DisplayEntityData(std::string p_tab) override;
	void		SetColor(glm::vec3 p_newColor);

private:
	glm::vec3 c_color;
	void  BeginDraw();
	void  EndDraw();
	float NormalizeValue(float p_value);
};

