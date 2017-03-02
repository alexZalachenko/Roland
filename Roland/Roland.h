#pragma once
#include "RolandUtilities.h"
class IGraphicEngine;

class Roland
{
public:
	Roland(Rol::RenderEngines p_renderEngine, Rol::WindowData p_windowData);
	~Roland();
	IGraphicEngine* GetGraphicEngine() { return c_graphicEngine; };

private:
	IGraphicEngine* c_graphicEngine;
};

