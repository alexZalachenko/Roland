#pragma once
#include <vector>
#include <string>
#include "RolandUtilities.h"
class IResource;
class IResourcesLoader;

class ResourcesManager
{
public:
	ResourcesManager(Rol::RenderEngines p_usedEngine);
	~ResourcesManager();
	IResource* GetResource(std::string p_name);

private:
	Rol::RenderEngines		c_usedEngine;
	std::vector<IResource*>	c_resources;
	IResourcesLoader* c_resourcesLoader;
	IResource* LoadFile(std::string p_file);
};

