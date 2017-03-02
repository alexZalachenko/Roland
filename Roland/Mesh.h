#pragma once
#include "Entity.h"
#include <string>
class MeshResource;

class Mesh : public Entity
{
public:
	Mesh();
	~Mesh();

private:
	MeshResource* c_mesh;
	void LoadMesh(std::string p_file);
	void BeginDraw();
	void EndDraw();
};

