#include "Mesh.h"
#include "IMeshResource.h"
#include "Image.h"
#include "ModelMatrix.h"
#include <iostream>

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

void Mesh::DisplayEntityData(std::string p_tab)
{
	std::cout << p_tab << "Entity type: mesh" << std::endl;
	if (c_meshResource != nullptr)
		c_meshResource->DisplayResourceData(p_tab);
}
