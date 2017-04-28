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

	void AddObject(std::string p_name) override;
	void AddVertices(std::vector<Rol::Vertex> p_vertices) override;
	void AddFaces(std::vector<unsigned int> p_faces) override;
	bool CheckIfValidObject(int p_valueToCheck);//0=vertices 1=faces. Returns true if vertices/faces can be added

private:
	std::vector<unsigned int> c_vao;
	std::vector<unsigned int> c_vbo;
	std::vector<unsigned int> c_ebo;
	void SetupData();
};

