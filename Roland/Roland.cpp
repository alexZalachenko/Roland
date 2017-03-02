#include "Roland.h"
#include "IGraphicEngine.h"
#include "OpenGLEngine.h"
#include <iostream>

Roland::Roland(Rol::RenderEngines p_renderEngine, Rol::WindowData p_windowData)
{
	switch (p_renderEngine)
	{
		case Rol::OpenGL:
			c_graphicEngine = new OpenGLEngine();
			break;
		case Rol::DirectX:
			break;
		default:
			std::cout << "Selected Render engine does not exist. Closing application" << std::endl;
			exit(-1);
			break;
	}
	c_graphicEngine->SetupEngine(p_windowData);
	c_graphicEngine->StartLoop();
	c_graphicEngine->Terminate();
}

Roland::~Roland()
{
	delete c_graphicEngine;
}