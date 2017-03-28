#include "MeshResource.h"
#include "MeshData.h"

MeshResource::MeshResource()
{
	c_vertices = std::vector<Vertex>();
}

MeshResource::~MeshResource()
{
	if (c_meshData != nullptr)
		delete c_meshData;
}

void MeshResource::Draw()
{
	if (c_meshData != nullptr)
		c_meshData->Draw();
}
