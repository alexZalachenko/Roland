#pragma once
#include "IEntity.h"
class MeshResource;

class Mesh : public IEntity
{
public:
	Mesh();
	~Mesh();
	void SetMeshResource(MeshResource* p_meshResource) { c_meshResource = p_meshResource; }
	MeshResource* GetMeshResource() { return c_meshResource; }

private:
	MeshResource* c_meshResource;
	void BeginDraw();
	void EndDraw();
};

