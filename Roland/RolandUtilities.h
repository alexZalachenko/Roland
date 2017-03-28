#pragma once
#include <string>

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
}