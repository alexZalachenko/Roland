#include "Resource.h"

Resource::Resource()
{
}

Resource::~Resource()
{
}

std::string Resource::GetName()
{
	return c_name;
}

void Resource::SetName(std::string p_name)
{
	c_name = p_name;
}
