#pragma once
#include <vector>
#include <string>
class Resource;

class ResourcesManager
{
public:
	ResourcesManager();
	~ResourcesManager();
	Resource* GetResource(std::string p_name);

private:
	std::vector<Resource> c_resources;
};

