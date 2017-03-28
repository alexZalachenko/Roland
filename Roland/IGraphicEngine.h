#pragma once
#include "RolandUtilities.h"
#include "Node.h"
class IEntity;
class IGraphicEngine;
class Transform;
class Camera;
class Light;
#include "Mesh.h"
#include "ResourcesManager.h"

/*
Interface that every implementation of the graphic engine must inherit.
By this is granted that every graphic engine implemented has the following functionality
*/
class IGraphicEngine
{
public:
	IGraphicEngine(Rol::RenderEngines p_usedEngine)
		:c_usedEngine(p_usedEngine),
		 c_resourcesManager(p_usedEngine)
	{
	};
	virtual ~IGraphicEngine() {};
	virtual void       SetupEngine(Rol::WindowData p_windowData) = 0;
	virtual void       StartLoop() = 0;
	virtual void       Terminate() = 0;
	virtual Node*      CreateNode(Node* p_father, IEntity* p_IEntity) = 0;
	virtual Node*      CreateNode() = 0;
	virtual Transform* CreateTransform() = 0;
	virtual Camera*    CreateCamera() = 0;
	virtual Light*     CreateLight() = 0;
	virtual Mesh*      CreateMesh(std::string p_file) = 0;
	virtual void	   DeleteMesh(std::string p_file) = 0;
			Node*	   GetRootNode() { return &c_rootNode; }
			void	   AddNodeToRoot(Node* p_node) { c_rootNode.AddChildren(p_node); }

protected:
	Node c_rootNode;
	ResourcesManager	c_resourcesManager;
	Rol::RenderEngines	c_usedEngine;
};

