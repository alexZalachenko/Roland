#pragma once
#include "RolandUtilities.h"
class Node;
class Entity;
class IGraphicEngine;
class Transform;
class Camera;
class Light;
class Mesh;
class ResourcesManager;

class IGraphicEngine
{
public:
	IGraphicEngine(){};
	virtual ~IGraphicEngine(){};
	virtual void       SetupEngine(Rol::WindowData p_windowData) = 0;
	virtual void       StartLoop() = 0;
	virtual void       Terminate() = 0;
	virtual Node*      CreateNode(Node* p_father, Entity* p_entity) = 0;
	virtual Transform* CreateTransform() = 0;
	virtual Camera*    CreateCamera() = 0;
	virtual Light*     CreateLight() = 0;
	virtual Mesh*      CreateMesh(std::string p_file) = 0;
			Node*	   GetRootNode() { return c_rootNode; }

protected:
	Node* c_rootNode;
	ResourcesManager* c_resourcesManager;
};

