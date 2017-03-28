#include "MeshOpenGLData.h"
#define GLEW_STATIC //use static binding. All the code used from the library is put into the executable and no needed to attach a dll
#include <GL/glew.h>//for abstracting cumbersome OpenGL procedures
#include <glm\vec3.hpp>
#include "MeshResource.h"

MeshOpenGLData::MeshOpenGLData(MeshResource* p_meshResource)
{
	c_vbo = std::vector<unsigned int>();

	//VAO (stores vertex attribute configurations (vertexAttribPointer, VertexAttribArray) and the VBO to use)
	glGenVertexArrays(1, &c_vao);			//create VAO container and get ID for it
	glBindVertexArray(c_vao);				//bind to OpenGL context
	//VBO
	unsigned int t_vbo;
	glGenBuffers(1, &t_vbo);				//create
	glBindBuffer(GL_ARRAY_BUFFER, t_vbo);	//bind
	glBufferData(							//fill
		GL_ARRAY_BUFFER,
		sizeof(Vertex) * p_meshResource->GetVertices().size(),
		&p_meshResource->GetVertices()[0],
		GL_STATIC_DRAW);
	//buffer is binded. Set pipes
	//pipe 0 for the vertex shader
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);			
	glEnableVertexAttribArray(1); 
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)12);

	glBindVertexArray(0);//unbind the VAO
	c_vbo.push_back(t_vbo);
}

MeshOpenGLData::~MeshOpenGLData()
{
	//delete the VAO
	glDeleteVertexArrays(1, &c_vao);
	//delete the VBO
	glDeleteBuffers(c_vbo.size(), &c_vbo[0]);
}

void MeshOpenGLData::Draw()
{
	glBindVertexArray(c_vao);//bind the VAO
	glDrawArrays(GL_TRIANGLES, 0, 3);//TODO
	glBindVertexArray(0);//unbind the VAO
}
