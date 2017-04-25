#include "ResourcesManager.h"
#include "ResourcesLoaderOpenGL.h"
#include "IResource.h"
#include <iostream>
#include <regex>

ResourcesManager::ResourcesManager(Rol::RenderEngines p_usedEngine)
	:c_usedEngine(p_usedEngine)
{
	c_resources = std::vector<IResource*>();
	switch (c_usedEngine)
	{
	case Rol::OpenGL:
		c_resourcesLoader = new ResourcesLoaderOpenGL();
		break;
	case Rol::DirectX:
		std::cout << "DirectX not implemented yet" << std::endl;
		break;
	}
}

ResourcesManager::~ResourcesManager()
{
	for (IResource* t_resource : c_resources)
		delete t_resource;
}

IResource* ResourcesManager::GetResource(std::string p_name)
{
	for (IResource* t_resource : c_resources)
	{
		if (t_resource->GetName() == p_name)
			return t_resource;
	}
	//the resource is not on the resources inventory. Load it
	if (LoadFile(p_name) != nullptr)
		return c_resources.back();
	else
		return nullptr;
}

IResource* ResourcesManager::LoadFile(std::string p_file)
{
	IResource* t_loadedResource = nullptr;
	//check if the file is an image
	if (std::regex_match(p_file, std::regex{ R"(.*\.(png|jpg)$)" }))
		t_loadedResource = c_resourcesLoader->LoadImage(p_file);
	//check if the file is a mesh
	else if (std::regex_match(p_file, std::regex{ R"(.*\.(obj|3ds|FBX|blend)$)" }))
		t_loadedResource = c_resourcesLoader->LoadMesh(p_file);

	//check if the file existed
	if (t_loadedResource == nullptr)
		std::cout << "Error. File not found" << std::endl;
	else
		c_resources.push_back(t_loadedResource);
	return t_loadedResource;
}

