#include "Image.h"
#include "IImageResource.h"
#include <iostream>

Image::Image()
	: IEntity(ImageType),
	  c_imageResource(nullptr)
{
}

Image::~Image()
{
}

void Image::BeginDraw()
{
	if (c_imageResource != nullptr)
		c_imageResource->Display();
}

void Image::EndDraw()
{
}

void Image::DisplayEntityData(std::string p_tab)
{
	std::cout << p_tab << "Entity type: image	" << std::endl;
	if (c_imageResource != nullptr)
		c_imageResource->DisplayResourceData(p_tab);
}
