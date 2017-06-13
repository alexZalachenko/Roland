#pragma once
#include "IResource.h"

class IImageResource : public IResource
{
public:
	IImageResource(std::string p_name, int p_width, int p_height)
		:IResource(p_name),
		 c_width(p_width),
		 c_height(p_height)
	{
	}
	IImageResource(int p_width, int p_height)
		:c_width(p_width),
		 c_height(p_height)
	{
	}
	~IImageResource()
	{
	}
	void Display() = 0;

protected:
	int c_width;
	int c_height;
};

