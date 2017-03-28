#pragma once
#include "MeshData.h"
#include <vector>
class MeshResource;

class MeshOpenGLData : public MeshData
{
public:
	MeshOpenGLData(MeshResource* p_meshResource);
	~MeshOpenGLData();
	void Draw();
private:
	unsigned int c_vao;
	std::vector<unsigned int> c_vbo;
};

