#pragma once
#include "IImageResource.h"

class ImageResourceOpenGL : public IImageResource
{
public:
	ImageResourceOpenGL(int p_width, int p_height, int t_imageData);
	~ImageResourceOpenGL();
	void Display() override;

private:
	unsigned int c_imageData;
};

