#pragma once
#include "IEntity.h"
class IMeshResource;
class Image;
class ModelMatrix;

class Mesh : public IEntity
{
public:
	Mesh(ModelMatrix* p_modelMatrix);
	~Mesh();
	void SetMeshResource(IMeshResource* p_meshResource) { c_meshResource = p_meshResource; }
	IMeshResource* GetMeshResource() { return c_meshResource; }
	void SetTexture(Image* p_texture);
	ModelMatrix* c_modelMatrix;
	void DisplayEntityData(std::string p_tab) override;

private:
	IMeshResource* c_meshResource;
	void BeginDraw();
	void EndDraw();
};

