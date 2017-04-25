#pragma once
#include "IEntity.h"
class IMeshResource;
class Image;

class Mesh : public IEntity
{
public:
	Mesh();
	~Mesh();
	void SetMeshResource(IMeshResource* p_meshResource) { c_meshResource = p_meshResource; }
	IMeshResource* GetMeshResource() { return c_meshResource; }
	void SetTexture(Image* p_texture);

private:
	IMeshResource* c_meshResource;
	void BeginDraw();
	void EndDraw();
};

