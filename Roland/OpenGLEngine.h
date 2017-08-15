#pragma once
#include <vector>
#include "IGraphicEngine.h"
#include "RolandUtilities.h"
#define GLEW_STATIC //use static binding. All the code used from the library is put into the executable and no needed to attach a dll
#include <GL/glew.h>//for abstracting cumbersome OpenGL procedures
#include <map>
#include "glm\mat4x4.hpp"
#include "ModelMatrix.h"
struct GLFWwindow;

class OpenGLEngine : public IGraphicEngine
{
public:
	OpenGLEngine();
	~OpenGLEngine();
	//inherited from IGraphicEngine
	void			SetupEngine(Rol::WindowData p_windowData) override;
	void			StartLoop() override;
	void			Terminate() override;
	Node*			CreateNode(Node* p_father, IEntity* p_IEntity) override;
	Node*			CreateNode() override;
	Transform*		CreateTransform() override;
	Camera*			CreatePerspectiveCamera(float p_far, float p_near, float p_fov, float p_width, float p_height) override;
	Camera*			CreateOrthographicCamera(float p_near, float p_far, float p_left, float p_right, float p_top, float p_bottom) override;
	Light*			CreateLight() override;
	Light*			CreateLight(glm::vec3 p_intensity) override;
	Mesh*			CreateMesh(std::string p_file) override;
	Mesh*			CreateMesh(std::string p_meshFile, std::string p_textureFile) override;
	void			DeleteMesh(std::string p_file) override;
	Image*			CreateImage(std::string p_file) override;
	void			DeleteImage(std::string p_file) override;
	void			RegisterLightNode(Node* p_lightNode) override;
	void			SetActiveCamera(Node* p_cameraNode) override;
	FPSCamera*		CreateFPSCamera(float p_far, float p_near, float p_fov, float p_width, float p_height) override;
	void			DisplayScenetreeData() override;
	void			CreateNewProgram(std::string p_vertexShader, std::string p_fragmentShader, std::string p_programName) override;
	void			Draw();

private:
	GLFWwindow*			c_window;
	std::vector<Node*>	c_lights;
	glm::mat4			c_projectionMatrix;
	ModelMatrix			c_modelMatrix;
	glm::mat4			c_viewMatrix;
	GLuint				c_viewMatrixLocation;

	void	Init();
	void	CreateWindow(Rol::WindowData p_windowData);
	void	InitGlew();
	void	InitCallbacks();
};

