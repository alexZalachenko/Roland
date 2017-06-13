#include "ImageResourceOpenGL.h"
#define GLEW_STATIC //use static binding. All the code used from the library is put into the executable and no needed to attach a dll
#include <GL/glew.h>//for abstracting cumbersome OpenGL procedures
#include <iostream>

ImageResourceOpenGL::ImageResourceOpenGL(std::string p_name, int p_width, int p_height, int t_imageData)
	:IImageResource(p_name, p_width, p_height),
	 c_imageData(t_imageData)
{
}

ImageResourceOpenGL::ImageResourceOpenGL(int p_width, int p_height, int t_imageData)
	:IImageResource(p_width, p_height),
	 c_imageData(t_imageData)
{
}

ImageResourceOpenGL::~ImageResourceOpenGL()
{
}

void ImageResourceOpenGL::Display()
{
	glBindTexture(GL_TEXTURE_2D, c_imageData);
}

void ImageResourceOpenGL::DisplayResourceData(std::string p_tab)
{
	std::cout << p_tab << "Image name: " << c_name;
	std::cout << p_tab << "Height: " << c_height << " Width: " << c_width << "OpenGL texture index: " << c_imageData << std::endl;
}
