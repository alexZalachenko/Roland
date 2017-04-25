#pragma once
#include <vector>
#include "IMeshResource.h"

class MeshResourceOpenGL : public IMeshResource
{
public:
	MeshResourceOpenGL(std::vector<Rol::Vertex> p_vertices);
	MeshResourceOpenGL(std::vector<Rol::Vertex> p_vertices, std::string p_name);
	MeshResourceOpenGL(std::vector<Rol::Vertex> p_vertices, std::vector<unsigned int> p_indices);
	MeshResourceOpenGL(std::vector<Rol::Vertex> p_vertices, std::vector<unsigned int> p_indices, std::string p_name);
	~MeshResourceOpenGL();
	void Display() override;

private:
	unsigned int c_vao;
	std::vector<unsigned int> c_vbo;
	unsigned int c_ebo;
	void SetupData();
};

