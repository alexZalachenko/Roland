#pragma once
#include <vector>
#include "IMeshResource.h"

class MeshResourceOpenGL : public IMeshResource
{
public:
	MeshResourceOpenGL();
	MeshResourceOpenGL(std::string p_name);
	~MeshResourceOpenGL();
	void Display() override;
	void CreateMesh(std::string p_name, std::vector<Rol::Vertex> p_vertices, std::vector<unsigned int> p_indices) override;
	virtual void CreateMesh(std::vector<Rol::Vertex> p_vertices, std::vector<unsigned int> p_indices) override;
	virtual void CreateMesh(std::vector<Rol::Vertex> p_vertices) override;
	virtual void DisplayMeshData() override;

private:
	unsigned int c_vao;
	unsigned int c_vbo;
	unsigned int c_ebo;
	void CreateBufferObjects();
};

