#include "ResourcesManager.h"
#include "Resource.h"

ResourcesManager::ResourcesManager()
{
}

ResourcesManager::~ResourcesManager()
{
}

Resource* ResourcesManager::GetResource(std::string p_name)
{
	for (size_t t_index = 0; t_index < c_resources.size; t_index++)
	{
		if (c_resources[t_index].GetName() == p_name)
			return &c_resources[t_index];
	}
	Resource t_newResource = Resource();
	//cargar fichero
	//TODO
	c_resources.push_back(t_newResource);
	return &t_newResource;
}