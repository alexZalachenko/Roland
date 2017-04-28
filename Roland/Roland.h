#pragma once
class IGraphicEngine;
#include "RolandUtilities.h"
/*
Roland is the main class which holds actual graphic library used (OpenGL, DirectX). 
Roland recives the parameters for creating a window and the desired graphic library
*/
class Roland
{
public:
	Roland(Rol::RenderEngines p_renderEngine, Rol::WindowData p_windowData);
	~Roland();
	void StartEngine();
	IGraphicEngine* GetGraphicEngine() { return c_graphicEngine; };

private:
	IGraphicEngine* c_graphicEngine;
};

