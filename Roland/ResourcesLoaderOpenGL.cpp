#include "ResourcesLoaderOpenGL.h"
#include <glm\vec3.hpp>
#include <glm\vec4.hpp>
#include <SOIL\SOIL.h>
#include "ImageResourceOpenGL.h"
#include "MeshResourceOpenGL.h"
#define GLEW_STATIC //use static binding. All the code used from the library is put into the executable and no needed to attach a dll
#include <GL/glew.h>//for abstracting cumbersome OpenGL procedures
#include <iostream>
#include <fstream>

//for loading resources using OpenGL specific techniques

ResourcesLoaderOpenGL::ResourcesLoaderOpenGL()
{
}

ResourcesLoaderOpenGL::~ResourcesLoaderOpenGL()
{
}

IResource* ResourcesLoaderOpenGL::LoadImage(std::string p_file)
{
	int t_width, t_height;
	unsigned char* t_imageData = SOIL_load_image(p_file.c_str(), &t_width, &t_height, 0, SOIL_LOAD_RGB);
	if (t_imageData == 0)
		return nullptr;

	glActiveTexture(GL_TEXTURE0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

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
	bool t_firstObject = true;
	std::vector<Rol::Vertex> t_vertices;
	std::vector<unsigned int> t_facesIndex;
	MeshResourceOpenGL* t_newMeshResource = new MeshResourceOpenGL();

	if (p_file == "fakeMesh.obj")
	{
		t_vertices.push_back(
			Rol::Vertex(
				glm::vec3(0.5f, 0.5f, 0.0f),
				glm::vec4(1.f, 0.f, 0.f, 1.f),
				glm::vec2(1.f, 1.f)));
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
		t_facesIndex.push_back(0);
		t_facesIndex.push_back(1);
		t_facesIndex.push_back(3);
		t_facesIndex.push_back(1);
		t_facesIndex.push_back(2);
		t_facesIndex.push_back(3);

		t_newMeshResource->CreateMesh(t_vertices, t_facesIndex);
		return t_newMeshResource;
	}
	
	std::ifstream t_fileReader(p_file, std::ifstream::in);
	if (!t_fileReader)
		return nullptr;

	std::string t_line;
	char* t_nextToken = nullptr;
	while (std::getline(t_fileReader, t_line))
	{
		//comment
		if (t_line[0] == '#')
			continue;
		//new object
		if (t_line[0] == 'o')
		{
			//if (!t_firstObject)
			//{
			//	//t_newMeshResource->AddVertices(t_vertices);
			//	//t_vertices.clear();
			//	//t_newMeshResource->AddFaces(t_facesIndex);
			//	//t_facesIndex.clear();
			//}
			////create the new object
			//t_newMeshResource->AddObject(t_line.substr(1));
		}
		//new vertex
		if (t_line[0] == 'v' && t_line[1] == ' ')
		{
			strtok_s(&t_line[0u], " ", &t_nextToken);
			float x = std::stof(strtok_s(NULL, " ", &t_nextToken));
			float y = std::stof(strtok_s(NULL, " ", &t_nextToken));
			float z = std::stof(strtok_s(NULL, " ", &t_nextToken));
			t_vertices.push_back(Rol::Vertex(
				glm::vec3(
					x,
					y, 
					z
				)
			));
		}
		//new face
		if (t_line[0] == 'f')
		{
			//only accept triangle faces
			strtok_s(&t_line[0u], " ", &t_nextToken);
			std::string t_face;
			for (size_t t_index = 0; t_index < 3; ++t_index)
			{
				t_face = strtok_s(NULL, " ", &t_nextToken);
				t_facesIndex.push_back(atoi(t_face.substr(0, t_face.find("/")).c_str()));
			}
		}
	}
	t_newMeshResource->CreateMesh(t_vertices, t_facesIndex);
	return t_newMeshResource;
}
