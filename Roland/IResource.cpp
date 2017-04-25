#include "IResource.h"

IResource::IResource()
	:c_name("unnamedResource")
{
}

IResource::IResource(std::string p_name)
	: c_name(p_name)
{
}

IResource::~IResource()
{
}

std::string IResource::GetName()
{
	return c_name;
}

void IResource::SetName(std::string p_name)
{
	c_name = p_name;
}
