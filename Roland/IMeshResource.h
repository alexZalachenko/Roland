#pragma once
#include "IResource.h"
#include "glm\vec3.hpp"
#include "glm\vec4.hpp"
#include <vector>
#include "RolandUtilities.h"
class IImageResource;

class IMeshResource : public IResource
{
public:
	IMeshResource()
		:c_imageResource(nullptr)
	{
	}
	IMeshResource(std::string p_name)
		:IResource(p_name),
		 c_imageResource(nullptr)
	{
	}
	virtual ~IMeshResource()
	{
	}
	virtual void CreateMesh(std::string p_name, std::vector<Rol::Vertex> p_vertices, std::vector<unsigned int> p_indices) = 0;
	virtual void CreateMesh(std::vector<Rol::Vertex> p_vertices, std::vector<unsigned int> p_indices) = 0;
	virtual void CreateMesh(std::vector<Rol::Vertex> p_vertices) = 0;
	void SetTexture(IImageResource* p_texture) { c_imageResource = p_texture; }
	IImageResource* GetImageResource() { return c_imageResource; }
	virtual void Display() = 0;
	virtual void SetColors(glm::vec3 p_diffuseColor, glm::vec3 p_ambientColor, glm::vec3 p_specularColor, float p_specularComponent) = 0;

protected:
	std::vector<Rol::Vertex> c_vertices;
	std::vector<unsigned int> c_indices;
	IImageResource* c_imageResource;
	glm::vec3 c_diffuseColor;
	glm::vec3 c_ambientColor;
	glm::vec3 c_specularColor;
	float c_specularExponent;
};

