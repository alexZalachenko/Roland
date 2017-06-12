#include "Mesh.h"
#include "IMeshResource.h"
#include "Image.h"
#include "ModelMatrix.h"

Mesh::Mesh(ModelMatrix* p_modelMatrix)
	: IEntity(MeshType)
	, c_modelMatrix(p_modelMatrix)
{
}

Mesh::~Mesh()
{
	if (c_meshResource != nullptr)
		delete c_meshResource;
}

void Mesh::BeginDraw()
{
	if (c_meshResource != nullptr)
	{
		c_modelMatrix->ModelMatrixToShader();
		c_meshResource->Display();
	}
}

void Mesh::EndDraw()
{

}

void Mesh::SetTexture(Image* p_texture)
{
	if (c_meshResource != nullptr)
		c_meshResource->SetTexture(p_texture->GetImageResource());
}

void Mesh::DisplayMeshData()
{
	if (c_meshResource != nullptr)
		c_meshResource->DisplayMeshData();
}
