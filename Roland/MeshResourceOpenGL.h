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
	virtual void DisplayResourceData(std::string p_tab) override;
	virtual void SetColors(glm::vec3 p_diffuseColor, glm::vec3 p_ambientColor, glm::vec3 p_specularColor, float p_specularComponent) override;

private:
	unsigned int c_vao;
	unsigned int c_vbo;
	unsigned int c_ebo;
	void CreateBufferObjects();
};

