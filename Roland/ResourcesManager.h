#pragma once
#include <vector>
#include <string>
#include "RolandUtilities.h"
class Resource;

class ResourcesManager
{
public:
	ResourcesManager(Rol::RenderEngines p_usedEngine);
	~ResourcesManager();
	Resource* GetResource(std::string p_name);

private:
	Rol::RenderEngines		c_usedEngine;
	std::vector<Resource*>	c_resources;
	Resource* LoadFile(std::string p_file);
};

