#pragma once
#include <vector>
#include "IGraphicEngine.h"
#include "RolandUtilities.h"
#define GLEW_STATIC //use static binding. All the code used from the library is put into the executable and no needed to attach a dll
#include <GL/glew.h>//for abstracting cumbersome OpenGL procedures
#include <map>
struct GLFWwindow;

class OpenGLEngine : public IGraphicEngine
{
public:
	OpenGLEngine();
	~OpenGLEngine();
	//inherited from IGraphicEngine
	void		SetupEngine(Rol::WindowData p_windowData) override;
	void		StartLoop() override;
	void		Terminate() override;
	Node*		CreateNode(Node* p_father, IEntity* p_IEntity) override;
	Node*		CreateNode() override;
	Transform*  CreateTransform() override;
	Camera*		CreateCamera() override;
	Light*		CreateLight() override;
	Mesh*		CreateMesh(std::string p_file) override;
	void		DeleteMesh(std::string p_file) override;
	void		RegisterLightNode(Node* p_lightNode);
	void		RegisterCameraNode(Node* p_cameraNode);
	void		Draw();

private:
	GLFWwindow*			c_window;
	GLuint				c_shaderProgram;
	std::vector<Node*>	c_lights;
	std::vector<Node*>	c_cameras;

	void	Init();
	void	CreateWindow(Rol::WindowData p_windowData);
	void	InitGlew();
	void	InitCallbacks();
	GLuint	CompileShader(const GLchar* p_shaderFile, unsigned short p_shaderType);
	void	LinkShader(GLuint p_shader);
};

