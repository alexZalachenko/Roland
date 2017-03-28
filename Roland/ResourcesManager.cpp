#include "ResourcesManager.h"
#include "Resource.h"
#include "MeshResource.h"
#include "MeshOpenGLData.h"
#include <iostream>

ResourcesManager::ResourcesManager(Rol::RenderEngines p_usedEngine)
	:c_usedEngine(p_usedEngine)
{
	c_resources = std::vector<Resource*>();
}

ResourcesManager::~ResourcesManager()
{
	for (Resource* t_resource : c_resources)
		delete t_resource;
}

Resource* ResourcesManager::GetResource(std::string p_name)
{
	for (Resource* t_resource : c_resources)
	{
		if (t_resource->GetName() == p_name)
			return t_resource;
	}
	//the resource is not on the resources inventory. Load it
	c_resources.push_back(LoadFile(p_name));
	return c_resources.back();
}

Resource* ResourcesManager::LoadFile(std::string p_file)
{
	//TODO
	MeshResource* t_newResource = new MeshResource();
	
	if (p_file == "fakeMesh")
	{
		t_newResource->AddVertex(
			Vertex(
				glm::vec3(-0.5f, -0.5f, 0.0f),
				glm::vec4(1.f, 0.f, 0.f, 1.f)));
		t_newResource->AddVertex(
			Vertex(
				glm::vec3(0.5f, -0.5f, 0.0f),
				glm::vec4(0.f, 1.f, 0.f, 1.f)));
		t_newResource->AddVertex(
			Vertex(
				glm::vec3(0.0f, 0.5f, 0.0f),
				glm::vec4(0.f, 0.f, 1.f, 1.f)));
		t_newResource->SetName("recurso 1");

		switch (c_usedEngine)
		{
		case Rol::OpenGL:
			t_newResource->SetMeshData(new MeshOpenGLData(t_newResource));
			break;
		case Rol::DirectX:
			std::cout << "DirectX not implemented yet" << std::endl;
			break;
		}
	}
	return t_newResource;
}

