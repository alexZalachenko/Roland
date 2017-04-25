#pragma once
#include "IResourcesLoader.h"

class ResourcesLoaderOpenGL : public IResourcesLoader
{
public:
	ResourcesLoaderOpenGL();
	~ResourcesLoaderOpenGL();
	IResource* LoadImage(std::string p_file) override;
	IResource* LoadMesh(std::string p_file) override;
};

