#pragma once
#include <string>
class Resource
{
public:
	Resource();
	virtual ~Resource();
	std::string GetName();
	void SetName(std::string p_name);

private:
	std::string c_name;
};

