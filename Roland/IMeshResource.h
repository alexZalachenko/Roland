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

	virtual void AddObject(std::string p_name) = 0;
	virtual void AddVertices(std::vector<Rol::Vertex> p_vertices) = 0;
	virtual void AddFaces(std::vector<unsigned int> p_faces) = 0;

	void SetTexture(IImageResource* p_texture) { c_imageResource = p_texture; }
	//methods for retrieving info about the mesh
	virtual void Display() = 0;
	

protected:
	std::vector<Rol::Object> c_objects;
	IImageResource* c_imageResource;
};

