#pragma once
#include "IEntity.h"
class IMeshResource;
class Image;
class ModelMatrix;
class ShadersManager;

class Mesh : public IEntity
{
public:
	Mesh(ModelMatrix* p_modelMatrix, ShadersManager* p_shadersManager);
	~Mesh();
	void SetMeshResource(IMeshResource* p_meshResource) { c_meshResource = p_meshResource; }
	IMeshResource* GetMeshResource() { return c_meshResource; }
	void SetTexture(Image* p_texture);
	ModelMatrix* c_modelMatrix;
	void DisplayEntityData(std::string p_tab) override;

private:
	IMeshResource* c_meshResource;
	ShadersManager* c_shadersManager;
	void BeginDraw();
	void EndDraw();
	unsigned int c_isTextureLocation;
};

