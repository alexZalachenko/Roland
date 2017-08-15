#include "Mesh.h"
#include "IMeshResource.h"
#include "Image.h"
#include "ModelMatrix.h"
#include <iostream>
#include "ShadersManager.h"

Mesh::Mesh(ModelMatrix* p_modelMatrix, ShadersManager* p_shadersManager)
	: IEntity(MeshType)
	, c_modelMatrix(p_modelMatrix)
	, c_shadersManager(p_shadersManager)
{
	c_isTextureLocation = glGetUniformLocation(c_shadersManager->GetActiveProgram(), "isTextured");
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
		if (c_meshResource->GetImageResource() != nullptr && c_isTextureLocation != 0)
			glUniform1i(c_isTextureLocation, 1);
		else
			glUniform1i(c_isTextureLocation, 0);
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
