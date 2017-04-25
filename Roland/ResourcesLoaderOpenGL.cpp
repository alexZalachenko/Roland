#include "ResourcesLoaderOpenGL.h"
#include <glm\vec3.hpp>
#include <glm\vec4.hpp>
#include <SOIL\SOIL.h>
#include "ImageResourceOpenGL.h"
#include "MeshResourceOpenGL.h"
#define GLEW_STATIC //use static binding. All the code used from the library is put into the executable and no needed to attach a dll
#include <GL/glew.h>//for abstracting cumbersome OpenGL procedures

/*
for loading resources using OpenGL specific techniques
*/

ResourcesLoaderOpenGL::ResourcesLoaderOpenGL()
{
}

ResourcesLoaderOpenGL::~ResourcesLoaderOpenGL()
{
}

IResource* ResourcesLoaderOpenGL::LoadImage(std::string p_file)
{
	glActiveTexture(GL_TEXTURE0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int t_width, t_height;
	unsigned char* t_imageData = SOIL_load_image(p_file.c_str(), &t_width, &t_height, 0, SOIL_LOAD_RGB);
	GLuint t_texture;
	glGenTextures(1, &t_texture);
	glBindTexture(GL_TEXTURE_2D, t_texture);
	// Set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, t_width, t_height, 0, GL_RGB, GL_UNSIGNED_BYTE, t_imageData);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(t_imageData);
	ImageResourceOpenGL* r_newResource = new ImageResourceOpenGL(t_width, t_height, t_texture);
	glBindTexture(GL_TEXTURE_2D, 0);
	return r_newResource;
}

IResource* ResourcesLoaderOpenGL::LoadMesh(std::string p_file)
{
	//read mesh vertices data using a library instead of this hardcoded
	std::vector<Rol::Vertex> t_vertices = std::vector<Rol::Vertex>();
	std::vector<unsigned int> t_indices{ 0,1,3,1,2,3 };

	if (p_file == "fakeMesh.obj")
	{
		t_vertices.push_back(
			Rol::Vertex(
				glm::vec3(0.5f, 0.5f, 0.0f),
				glm::vec4(1.f, 0.f, 0.f, 1.f),
				glm::vec2(1.f,1.f)));
		t_vertices.push_back(
			Rol::Vertex(
				glm::vec3(0.5f, -0.5f, 0.0f),
				glm::vec4(0.f, 1.f, 0.f, 1.f),
				glm::vec2(1.f, 0.f)));
		t_vertices.push_back(
			Rol::Vertex(
				glm::vec3(-0.5f, -0.5f, 0.0f),
				glm::vec4(0.f, 0.f, 1.f, 1.f),
				glm::vec2(0.f, 0.f)));
		t_vertices.push_back(
			Rol::Vertex(
				glm::vec3(-0.5f, 0.5f, 0.0f),
				glm::vec4(1.f, 1.f, 0.f, 1.f),
				glm::vec2(0.f, 1.f)));
	}
	//indexed drawing can be used or not
	return new MeshResourceOpenGL(t_vertices, t_indices);
}
