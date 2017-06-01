#include "MeshResourceOpenGL.h"
#define GLEW_STATIC //use static binding. All the code used from the library is put into the executable and no needed to attach a dll
#include <GL/glew.h>//for abstracting cumbersome OpenGL procedures
#include <glm\vec3.hpp>
#include "IMeshResource.h"
#include "IImageResource.h"
#include <iostream>

MeshResourceOpenGL::MeshResourceOpenGL()
{
}

MeshResourceOpenGL::MeshResourceOpenGL(std::string p_name)
	:IMeshResource(p_name)
{
}

MeshResourceOpenGL::~MeshResourceOpenGL()
{
	//delete the VAO
	glDeleteVertexArrays(1, &c_vao);
	//delete the VBO
	glDeleteBuffers(1, &c_vbo);
	//delete de EBO
	glDeleteBuffers(1, &c_ebo);
}

void MeshResourceOpenGL::Display()
{
	//does the mesh has a texture?
	if (c_imageResource != nullptr)
		c_imageResource->Display();

	glBindVertexArray(c_vao);                        //bind the VAO
	if (c_indices.empty())							 //are we using indexed drawing?
		glDrawArrays(GL_TRIANGLES, 0, c_vertices.size());
	else
		glDrawElements(GL_TRIANGLES, c_indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);                            //unbind the VAO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);        //unbind the EBO
	//TODO how to unbind the texture?
}

void MeshResourceOpenGL::CreateMesh(std::string p_name, std::vector<Rol::Vertex> p_vertices, std::vector<unsigned int> p_indices)
{
	c_vertices = p_vertices;
	c_indices = p_indices;
	//c_objects.push_back(Rol::Object(p_name));

	CreateBufferObjects();
	
	//EBO
	glGenBuffers(1, &c_ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, c_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, c_indices.size() * sizeof(unsigned int), &c_indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);					 //unbind the VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);		 //unbind the VAO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);//unbind the EBO
}

void MeshResourceOpenGL::CreateMesh(std::vector<Rol::Vertex> p_vertices, std::vector<unsigned int> p_indices)
{
	c_vertices = p_vertices;
	c_indices = p_indices;
	CreateBufferObjects();
	//EBO
	glGenBuffers(1, &c_ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, c_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, c_indices.size() * sizeof(unsigned int), &c_indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);					 //unbind the VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);		 //unbind the VAO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);//unbind the EBO
}

void MeshResourceOpenGL::CreateMesh(std::vector<Rol::Vertex> p_vertices)
{
	c_vertices = p_vertices;
	CreateBufferObjects();
	glBindVertexArray(0);					 //unbind the VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);		 //unbind the VAO
}

void MeshResourceOpenGL::CreateBufferObjects()
{
	//VAO (stores vertex attribute configurations (vertexAttribPointer, VertexAttribArray) and the VBO to use)
	glGenVertexArrays(1, &c_vao);			//create VAO container and get ID for it
	glBindVertexArray(c_vao);				//bind to OpenGL context

	//VBO
	glGenBuffers(1, &c_vbo);				//create
	glBindBuffer(GL_ARRAY_BUFFER, c_vbo);	//bind
	glBufferData(GL_ARRAY_BUFFER, c_vertices.size() * sizeof(Rol::Vertex), &c_vertices[0], GL_STATIC_DRAW);// load data into the buffer

	//set vertex attributes pointers
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Rol::Vertex), (void*)0); //position 
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Rol::Vertex), (void*)12);//color
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Rol::Vertex), (void*)24);//texture
}
