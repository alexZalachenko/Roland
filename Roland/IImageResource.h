#pragma once
#include "IResource.h"

class IImageResource : public IResource
{
public:
	IImageResource(int p_width, int p_height)
		:c_width(p_width),
		c_height(p_height)

	{
	}
	~IImageResource()
	{
	}
	void Display() = 0;

private:
	int c_width;
	int c_height;
};

