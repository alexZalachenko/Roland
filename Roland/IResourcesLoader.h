#pragma once
#include <string>
class IResource;

class IResourcesLoader
{
public:
	IResourcesLoader() {}
	virtual ~IResourcesLoader() {}
	virtual IResource* LoadImage(std::string p_file) = 0;
	virtual IResource* LoadMesh(std::string p_file) = 0;
	//virtual IResource LoadSound(std::string p_name) = 0;
};

