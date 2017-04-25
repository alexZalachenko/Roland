#include "Mesh.h"
#include "IMeshResource.h"
#include "Image.h"

Mesh::Mesh()
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
		c_meshResource->Display();
}

void Mesh::EndDraw()
{

}

void Mesh::SetTexture(Image* p_texture)
{
	if (c_meshResource != nullptr)
		c_meshResource->SetTexture(p_texture->GetImageResource());
}