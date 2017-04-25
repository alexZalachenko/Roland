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
	IMeshResource(std::vector<Rol::Vertex> p_vertices)
		:c_vertices(p_vertices),
		c_imageResource(nullptr)
	{
	}
	IMeshResource(std::vector<Rol::Vertex> p_vertices, std::string p_name)
		: IResource(p_name),
		c_vertices(p_vertices),
		c_imageResource(nullptr)
	{
	}
	IMeshResource(std::vector<Rol::Vertex> p_vertices, std::vector<unsigned int> p_indices)
		:c_vertices(p_vertices),
		 c_indices(p_indices),
		 c_imageResource(nullptr)
	{
	}
	IMeshResource(std::vector<Rol::Vertex> p_vertices, std::vector<unsigned int> p_indices, std::string p_name)
		:IResource(p_name),
		 c_vertices(p_vertices),
		 c_indices(p_indices),
		 c_imageResource(nullptr)
	{
	}
	virtual ~IMeshResource()
	{
	}
	std::vector<Rol::Vertex> GetVertices() { return c_vertices; }
	virtual void Display() = 0;
	void SetTexture(IImageResource* p_texture) { c_imageResource = p_texture; }

protected:
	std::vector<Rol::Vertex> c_vertices;
	std::vector<unsigned int> c_indices;
	IImageResource* c_imageResource;
};

