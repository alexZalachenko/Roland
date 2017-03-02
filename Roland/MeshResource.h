#pragma once
#include "Resource.h"

class MeshResource : public Resource
{
public:
	MeshResource();
	~MeshResource();
	void LoadFile(std::string p_name);
	void Draw();

private:
	long c_triangles;
	float* c_vertex;
	float* c_normals;
	float* c_textures;
	float* c_vertexTriangles;
	float* c_normalsTriangles;
	float* c_texturesTriangles;
};

