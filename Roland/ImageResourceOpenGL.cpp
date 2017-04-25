#include "ImageResourceOpenGL.h"
#define GLEW_STATIC //use static binding. All the code used from the library is put into the executable and no needed to attach a dll
#include <GL/glew.h>//for abstracting cumbersome OpenGL procedures

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
