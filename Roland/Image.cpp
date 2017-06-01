#include "Image.h"
#include "IImageResource.h"

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
