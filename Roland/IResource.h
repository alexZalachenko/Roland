#pragma once
#include <string>
class IResource
{
public:
	IResource();
	IResource(std::string p_name);
	virtual ~IResource();
	std::string GetName();
	void SetName(std::string p_name);
	virtual void Display() = 0;

private:
	std::string c_name;
};

