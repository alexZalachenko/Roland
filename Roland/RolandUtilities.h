#pragma once
#include <string>
#include <glm\vec3.hpp>
#include <glm\vec2.hpp>

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
			c_color			= glm::vec3(1, 1, 1);
			c_textureCoords = glm::vec2(0, 0);
		}
		Vertex(glm::vec3 p_position, glm::vec3 p_color)
			:c_position(p_position),
			 c_color(p_color)
		{
			c_textureCoords = glm::vec2(0, 0);
		}
		Vertex(glm::vec3 p_position, glm::vec3 p_color, glm::vec2 p_textureCoords)
			:c_position(p_position),
			 c_color(p_color),
			 c_textureCoords(p_textureCoords)
		{
		}

		glm::vec3 c_position;
		glm::vec3 c_color;
		glm::vec2 c_textureCoords;
	};
}