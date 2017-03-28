#include "Mesh.h"
#include "MeshResource.h"

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
		c_meshResource->Draw();
}

void Mesh::EndDraw()
{

}