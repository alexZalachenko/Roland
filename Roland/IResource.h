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
	virtual void DisplayResourceData(std::string p_tab) = 0;

protected:
	std::string c_name;
};

