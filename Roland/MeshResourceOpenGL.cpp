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
	glDeleteVertexArrays(c_vao.size(), &c_vao[0]);
	//delete the VBO
	glDeleteBuffers(c_vbo.size(), &c_vbo[0]);
	//delete de EBO
	glDeleteBuffers(c_ebo.size(), &c_ebo[0]);
}

void MeshResourceOpenGL::Display()
{
	//does the mesh has a texture?
	if (c_imageResource != nullptr)
		c_imageResource->Display();

	for (size_t t_object = 0; t_object < c_vao.size(); t_object++)
	{
		glBindVertexArray(c_vao[t_object]);				//bind the VAO
		glDrawElements(GL_TRIANGLES, c_objects[t_object].c_facesIndex.size() , GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);							//unbind the VAO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);		//unbind the EBO
	}
	
	//TODO how to unbind the texture?
}

void MeshResourceOpenGL::SetupData()
{
	////VAO (stores vertex attribute configurations (vertexAttribPointer, VertexAttribArray) and the VBO to use)
	//glGenVertexArrays(1, &c_vao);			//create VAO container and get ID for it
	//glBindVertexArray(c_vao);				//bind to OpenGL context
	////VBO
	//unsigned int t_vbo;
	//glGenBuffers(1, &t_vbo);				//create
	//glBindBuffer(GL_ARRAY_BUFFER, t_vbo);	//bind
	//glBufferData(GL_ARRAY_BUFFER, c_vertices.size() * sizeof(Rol::Vertex), &c_vertices[0], GL_STATIC_DRAW);// load data into the buffer

	////set vertex attributes pointers
	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Rol::Vertex), (void*)0);//position 
	//glEnableVertexAttribArray(1);
	//glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Rol::Vertex), (void*)12);//color
	//glEnableVertexAttribArray(2);
	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Rol::Vertex), (void*)24);//texture

	//c_vbo.push_back(t_vbo);
	//if (!c_indices.empty())
	//{
	//	//EBO
	//	glGenBuffers(1, &c_ebo);
	//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, c_ebo);
	//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, c_indices.size() * sizeof(unsigned int), &c_indices[0], GL_STATIC_DRAW);
	//}
	//
	//glBindVertexArray(0);					 //unbind the VBO
	//glBindBuffer(GL_ARRAY_BUFFER, 0);		 //unbind the VAO
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);//unbind the EBO
}

void MeshResourceOpenGL::AddObject(std::string p_name)
{
	//VAO (stores vertex attribute configurations (vertexAttribPointer, VertexAttribArray) and the VBO to use)
	unsigned int t_vao;
	glGenVertexArrays(1, &t_vao);			//create VAO container and get ID for it
	glBindVertexArray(t_vao);				//bind to OpenGL context
	c_vao.push_back(t_vao);

	c_objects.push_back(Rol::Object(p_name));
}

void MeshResourceOpenGL::AddVertices(std::vector<Rol::Vertex> p_vertices)
{
	if (CheckIfValidObject(0))
		c_objects.back().c_vertices = p_vertices;
	else
		return;
	//VBO
	unsigned int t_vbo;
	glGenBuffers(1, &t_vbo);				//create
	glBindBuffer(GL_ARRAY_BUFFER, t_vbo);	//bind
	glBufferData(GL_ARRAY_BUFFER, p_vertices.size() * sizeof(Rol::Vertex), &p_vertices[0], GL_STATIC_DRAW);// load data into the buffer
	c_vbo.push_back(t_vbo);

	//set vertex attributes pointers
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Rol::Vertex), (void*)0);//position 
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Rol::Vertex), (void*)12);//color
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Rol::Vertex), (void*)24);//texture
}

void MeshResourceOpenGL::AddFaces(std::vector<unsigned int> p_faces)
{
	if (CheckIfValidObject(1))
		c_objects.back().c_facesIndex = p_faces;
	else
		return;
	//EBO
	unsigned int t_ebo;
	glGenBuffers(1, &t_ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, t_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, p_faces.size() * sizeof(unsigned int), &p_faces[0], GL_STATIC_DRAW);
	c_ebo.push_back(t_ebo);

	glBindVertexArray(0);					 //unbind the VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);		 //unbind the VAO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);//unbind the EBO
}

bool MeshResourceOpenGL::CheckIfValidObject(int p_valueToCheck)
{
	if (c_objects.size() == 0)
	{
		std::cout << "Something went wrong. You are trying to add values to a meshResource but that mesh has no objects" << std::endl;
		return false;
	}
	switch (p_valueToCheck)
	{
	case 0:
		if (!c_objects.back().c_vertices.empty())
			std::cout << "You are adding vertices to the object " << c_objects.back().c_name << "which already has vertices. Are you missing something?" << std::endl;
		break;
	case 1:
		if (!c_objects.back().c_facesIndex.empty())
			std::cout << "You are adding faces to the object " << c_objects.back().c_name << "which already has faces. Are you missing something?" << std::endl;
		break;
	}
	return true;
}
