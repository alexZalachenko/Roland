#pragma once
#include "Resource.h"
#include "glm\vec3.hpp"
#include "glm\vec4.hpp"
#include <vector>
class MeshData;

struct Vertex
{
	Vertex() {};
	Vertex(glm::vec3 p_position, glm::vec3 p_color)
		:c_position(p_position),
		c_color(p_color)
	{

	}
	glm::vec3 c_position;
	glm::vec3 c_color;
};

class MeshResource : public Resource
{
public:
	MeshResource();
	~MeshResource();
	void AddVertex(Vertex p_vertex) { c_vertices.push_back(p_vertex); }
	std::vector<Vertex> GetVertices() { return c_vertices; }
	void Draw();
	void SetMeshData(MeshData* p_meshData) { c_meshData = p_meshData; }

private:
	MeshData* c_meshData;
	std::vector<Vertex> c_vertices;
	/*long c_triangles;
	float* c_vertex;
	float* c_normals;
	float* c_textures;
	float* c_vertexTriangles;
	float* c_normalsTriangles;
	float* c_texturesTriangles;*/
};

