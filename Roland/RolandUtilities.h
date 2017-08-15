#pragma once
#include <string>
#include <glm\vec4.hpp>
#include <glm\vec3.hpp>
#include <glm\vec2.hpp>
#include <vector>

namespace Rol
{
	enum RenderEngines
	{
		OpenGL,
		DirectX
	};

	struct WindowData
	{
		int c_width;
		int c_height;
		std::string c_title;
		bool c_fullscreen;
		bool c_resizable;
	};

	struct Vertex
	{
		Vertex(glm::vec3 p_position)
			:c_position(p_position)
		{
			c_color			= glm::vec4(1, 1, 1, 1);
			c_textureCoords = glm::vec2(0, 0);
		}
		Vertex(glm::vec3 p_position, glm::vec3 p_color)
			:c_position(p_position),
			 c_color(p_color, 1)
		{
			c_textureCoords = glm::vec2(0, 0);
		}
		Vertex(glm::vec3 p_position, glm::vec2 p_textureCoords)
			:c_position(p_position),
			 c_textureCoords(p_textureCoords)
		{
			c_color = glm::vec4(1, 1, 1, 1);
		}
		Vertex(glm::vec3 p_position, glm::vec3 p_color, glm::vec2 p_textureCoords)
			:c_position(p_position),
			 c_color(p_color, 1),
			 c_textureCoords(p_textureCoords)
		{
		}
		Vertex(glm::vec3 p_position, glm::vec3 p_color, glm::vec3 p_normal)
			:c_position(p_position),
			 c_color(p_color, 1),
			 c_normal(p_normal)
		{
		}
		Vertex(glm::vec3 p_position, glm::vec3 p_color, glm::vec3 p_normal, glm::vec2 p_textureCoords)
			:c_position(p_position),
			 c_color(p_color, 1),
			 c_normal(p_normal),
			 c_textureCoords(p_textureCoords)
		{
		}

		//redefine == operator
		bool operator==(const Vertex& t_vertex) {
			if (	c_position		== t_vertex.c_position
				&&	c_color			== t_vertex.c_color
				&&	c_textureCoords == t_vertex.c_textureCoords
				&&  c_normal		== t_vertex.c_normal)
			{
				return true;
			}
			return false;
		}

		glm::vec3 c_position;
		glm::vec4 c_color;
		glm::vec2 c_textureCoords;
		glm::vec3 c_normal;
	};
}