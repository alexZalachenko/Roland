#pragma once
#include "IEntity.h"
#include <string>

struct Color
{
	enum ColorName
	{
		red,
		green,
		blue
	};
	int c_red;
	int c_green;
	int c_blue;

	Color(int p_red, int p_green, int p_blue)
	{
		SetColor(red, p_red);
		SetColor(green, p_green);
		SetColor(blue, p_blue);
	}
	void SetColor(ColorName p_colorName, int p_value)
	{
		if (p_value < 0)
			p_value = 0;
		else if (p_value > 255)
			p_value = 255;

		switch (p_colorName)
		{
			case Color::red:
				c_red = p_value;
				break;
			case Color::green:
				c_green = p_value;
				break;
			case Color::blue:
				c_blue = p_value;
				break;
		}
	}
};

class Light : public IEntity
{
public:
	Light();
	Light(Color p_color);
	~Light();
	void SeIntensity(Color p_color);
	Color GetIntensity();
	bool GetIsActive();
	void SetIsActive(bool p_isActive);
	void DisplayEntityData(std::string p_tab) override;

private:
	Color c_intensity;
	bool c_isActive;
	void BeginDraw();
	void EndDraw();
};

