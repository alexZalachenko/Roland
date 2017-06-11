#pragma once
#include "RolandUtilities.h"
#include "ResourcesManager.h"
#include "Node.h"
#include "ResourcesManager.h"
#include "ShadersManager.h"
class Mesh;
class Image;
class IEntity;
class IGraphicEngine;
class Transform;
class Camera;
class Light;
class Image;
class FPSCamera;

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
	virtual void			SetupEngine(Rol::WindowData p_windowData) = 0;
	virtual void			StartLoop() = 0;
	virtual void			Terminate() = 0;
	virtual Node*			CreateNode(Node* p_father, IEntity* p_IEntity) = 0;
	virtual Node*			CreateNode() = 0;
	virtual Transform*		CreateTransform() = 0;
	virtual Camera*			CreatePerspectiveCamera(float p_far, float p_near, float p_fov, float p_width, float p_height) = 0;
	virtual Camera*			CreateOrthographicCamera(float p_near, float p_far, float p_left, float p_right, float p_top, float p_bottom) = 0;
	virtual Light*			CreateLight() = 0;
	virtual Mesh*			CreateMesh(std::string p_file) = 0;
	virtual Mesh*			CreateMesh(std::string p_meshFile, std::string p_textureFile) = 0;
	virtual void			DeleteMesh(std::string p_file) = 0;
	virtual Image*			CreateImage(std::string p_file) = 0;
	virtual void			DeleteImage(std::string p_file) = 0;
	virtual void			RegisterLightNode(Node* p_lightNode) = 0;
	virtual void			SetActiveCamera(Node* p_cameraNode) = 0;
	virtual FPSCamera*		CreateFPSCamera(float p_far, float p_near, float p_fov, float p_width, float p_height) = 0;
			Node*			GetRootNode() { return &c_rootNode; }
			void			AddNodeToRoot(Node* p_node) { c_rootNode.AddChildren(p_node); }

protected:
	Node				c_rootNode;
	Node*				c_activeCamera;
	ResourcesManager	c_resourcesManager;
	ShadersManager		c_shadersManager;
	Rol::RenderEngines	c_usedEngine;
};

