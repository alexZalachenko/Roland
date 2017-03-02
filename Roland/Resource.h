#pragma once
#include <string>
class Resource
{
public:
	Resource();
	virtual ~Resource();
	std::string GetName();

private:
	std::string c_name;
	void SetName(std::string p_name);
};

