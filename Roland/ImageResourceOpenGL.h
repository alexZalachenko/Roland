#pragma once
#include "IImageResource.h"

class ImageResourceOpenGL : public IImageResource
{
public:
	ImageResourceOpenGL(std::string p_name, int p_width, int p_height, int t_imageData);
	ImageResourceOpenGL(int p_width, int p_height, int t_imageData);
	~ImageResourceOpenGL();
	void Display() override;
	void DisplayResourceData(std::string p_tab) override;

private:
	unsigned int c_imageData;
};

