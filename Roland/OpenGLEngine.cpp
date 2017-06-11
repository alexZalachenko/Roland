#include "OpenGLEngine.h"
#include <GLFW/glfw3.h>//for creating a window and reading users' input
#include <iostream>
#include <fstream>
#include "CallbackFunctions.h"
#include "Node.h"
#include "IEntity.h"
#include "IGraphicEngine.h"
#include "Transform.h"
#include "Camera.h"
#include "Light.h"
#include "Mesh.h"
#include "IMeshResource.h"
#include "IImageResource.h"
#include "ResourcesManager.h"
#include "Image.h"
#include <regex>
#include "PerspectiveCamera.h"
#include "glm\gtc\type_ptr.hpp"
#include "FPSCamera.h"
#include "InputHandler.h"

OpenGLEngine::OpenGLEngine()
	: c_window(nullptr),
	IGraphicEngine(Rol::OpenGL)
{
	Init();
	
}

OpenGLEngine::~OpenGLEngine()
{
	//delete lights delete cameras
	Terminate();
}

				/*Methods related to engine's configuration*/
void			OpenGLEngine::SetupEngine(Rol::WindowData p_windowData)
{
	Init();
	CreateWindow(p_windowData);
	InitGlew();
	InitCallbacks();
	GLuint t_newProgram = c_shadersManager.CreateProgram("VertexShader.txt", "FragmentShader.txt", "program01");
	c_shadersManager.UseProgram(t_newProgram);
	c_modelMatrix.SetActiveProgram(t_newProgram);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_DEPTH_TEST);
}

void			OpenGLEngine::Terminate()
{
	glfwTerminate();
}

void			OpenGLEngine::Init()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void			OpenGLEngine::CreateWindow(Rol::WindowData p_windowData)
{
	p_windowData.c_resizable ? glfwWindowHint(GLFW_RESIZABLE, GL_TRUE) : glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	if (p_windowData.c_fullscreen)
	{
		const GLFWvidmode * t_mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		c_window = glfwCreateWindow(t_mode->width, t_mode->height, p_windowData.c_title.c_str(), glfwGetPrimaryMonitor(), nullptr);
	}
	else
		c_window = glfwCreateWindow(p_windowData.c_width, p_windowData.c_height, p_windowData.c_title.c_str(), nullptr, nullptr);

	if (c_window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		exit(-1);
	}
	glfwMakeContextCurrent(c_window);

	//here we create the viewport
	int t_width, t_height;
	glfwGetFramebufferSize(c_window, &t_width, &t_height);
	glViewport(0, 0, t_width, t_height);
	OpenGLCallbacks::c_halfHeight = t_height / 2.f;
	OpenGLCallbacks::c_halfWidth = t_width / 2.f;
}

void			OpenGLEngine::InitGlew()
{
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		exit(-1);
	}
}

void			OpenGLEngine::InitCallbacks()
{
	glfwSetKeyCallback(c_window, OpenGLCallbacks::HandleKeyboardInput);
	glfwSetCursorPosCallback(c_window, OpenGLCallbacks::HandleMouseMovementInput);
}

void			OpenGLEngine::StartLoop()
{
	while (!glfwWindowShouldClose(c_window))
	{
		// Check if any events have been activated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Clear the colorbuffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//draw the scene tree
		Draw();

		// Swap the screen buffers
		glfwSwapBuffers(c_window);
	}
}

				/*Methods related to engine's functionality*/
//user is responsible of freeing memory of the returned object
Node*			OpenGLEngine::CreateNode(Node* p_father, IEntity* p_IEntity)
{
	Node* t_newNode = new Node(p_father, p_IEntity);
	return t_newNode;
}

//user is responsible of freeing memory of the returned object
Node*			OpenGLEngine::CreateNode()
{
	Node* t_newNode = new Node();
	return t_newNode;
}

//user is responsible of freeing memory of the returned object
Transform*		OpenGLEngine::CreateTransform()
{
	Transform* t_newTransform = new Transform(&c_modelMatrix);
	return t_newTransform;
}

//set fov in degrees. user is responsible of freeing memory of the returned object
Camera*			OpenGLEngine::CreatePerspectiveCamera(float p_far, float p_near, float p_fov, float p_width, float p_height)
{
	Camera* t_newCamera = new PerspectiveCamera(p_far, p_near, p_fov, p_width, p_height);
	return t_newCamera;
}

//user is responsible of freeing memory of the returned object
Camera*			OpenGLEngine::CreateOrthographicCamera(float p_near, float p_far, float p_left, float p_right, float p_top, float p_bottom)
{
	return nullptr;
}

//user is responsible of freeing memory of the returned object
Light*			OpenGLEngine::CreateLight()
{
	//TODO
	Light* t_newLight = new Light;
	return t_newLight;
}

//user is responsible of freeing memory of the returned object
Mesh*			OpenGLEngine::CreateMesh(std::string p_file)
{
	if (!std::regex_match(p_file, std::regex{ R"(.*\.(obj|3ds|FBX|blend)$)" }))
	{
		std::cout << "Mesh format not supported" << std::endl;
		return nullptr;
	}

	Mesh* r_newMesh = new Mesh(&c_modelMatrix);
	//get the resource from the resources manager
	IResource* t_resource = c_resourcesManager.GetResource(p_file);
	//set it to the new created mesh
	if (t_resource != nullptr)
		r_newMesh->SetMeshResource(dynamic_cast<IMeshResource*>(t_resource));
	return r_newMesh;
}

//user is responsible of freeing memory of the returned object
Mesh*			OpenGLEngine::CreateMesh(std::string p_meshFile, std::string p_textureFile)
{
	Mesh* t_newMesh = CreateMesh(p_meshFile);//it might not have any IMeshResource or mesh be null
	if (t_newMesh != nullptr && t_newMesh->GetMeshResource() != nullptr)
	{
		Image* t_newImage = CreateImage(p_textureFile);
		if (t_newImage != nullptr)
			t_newMesh->GetMeshResource()->SetTexture(t_newImage->GetImageResource());
	}
	return t_newMesh;
}

//user is responsible of freeing memory of the returned object. The method might return nullptr value
Image*			OpenGLEngine::CreateImage(std::string p_file)
{
	if (!std::regex_match(p_file, std::regex{ R"(.*\.(png|jpg)$)" }))
	{
		std::cout << "Image format not supported" << std::endl;
		return nullptr;
	}

	Image* r_newImage = new Image;
	IResource* t_resource = c_resourcesManager.GetResource(p_file);
	if (t_resource != nullptr)
		r_newImage->SetImageResource(dynamic_cast<IImageResource*>(t_resource));
	return r_newImage;
}

void			OpenGLEngine::DeleteImage(std::string p_file)
{
	//TODO
}

//delete mesh from the resources manager. If the mesh is wanted again to be used it will must be loaded again
void			OpenGLEngine::DeleteMesh(std::string p_file)
{
	
	//TODO
}

void			OpenGLEngine::RegisterLightNode(Node* p_lightNode)
{
	if (p_lightNode != nullptr)
		c_lights.push_back(p_lightNode);
}

void			OpenGLEngine::SetActiveCamera(Node* p_cameraNode)
{
	if (p_cameraNode == nullptr || p_cameraNode->GetIEntity() == nullptr || p_cameraNode->GetIEntity()->GetEntityType() != CameraType)
		return;
	c_activeCamera = p_cameraNode;
	c_projectionMatrix = dynamic_cast<Camera*>(c_activeCamera->GetIEntity())->GetProjectionMatrix();
	GLuint t_projectionMatrixLocation = glGetUniformLocation(c_shadersManager.GetActiveProgram(), "projectionMatrix");
	glUniformMatrix4fv(t_projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(c_projectionMatrix));
}

FPSCamera*		OpenGLEngine::CreateFPSCamera(float p_far, float p_near, float p_fov, float p_width, float p_height)
{
	glfwSetInputMode(c_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	int t_width, t_height;
	glfwGetWindowSize(c_window, &t_width, &t_height);
	FPSCamera* t_newFPSCamera = new FPSCamera(p_far, p_near, p_fov, p_width, p_height, t_width/2.f, t_height/2.f);
	InputHandler::Instance()->RegisterInputReceiver(t_newFPSCamera);
	return t_newFPSCamera;
}

void			OpenGLEngine::Draw()
{
	//calculate viewMatrix
	if (c_activeCamera != nullptr)
	{
		std::vector<glm::mat4> t_transforms;
		//get all the transforms from the camera to the root of the scene tree
		Node* t_father = c_activeCamera->GetFather();
		while (t_father != nullptr)
		{
			if (t_father->GetIEntity() != nullptr && t_father->GetIEntity()->GetEntityType() == TransformType)
				t_transforms.push_back(((Transform*)t_father->GetIEntity())->GetMatrix());
			t_father = t_father->GetFather();
		}
		//multiply all the transforms from the leaf to the root
		//remember that last multiplication applied is the first. Last item in the vector is the first in the scene tree
		c_viewMatrix = ((Camera*)c_activeCamera->GetIEntity())->GetViewMatrix();
		for (auto it =  t_transforms.rbegin(); it != t_transforms.rend(); it++)
			c_viewMatrix *= (*it);
		//c_viewMatrix = glm::inverse(c_viewMatrix); //habria que descomentar
		
		GLuint t_matrixLocation = glGetUniformLocation(c_shadersManager.GetActiveProgram(), "viewMatrix");
		glUniformMatrix4fv(t_matrixLocation, 1, GL_FALSE, glm::value_ptr(c_viewMatrix));
	}

	//render lights
	for (size_t t_index = 0; t_index < c_lights.size(); ++t_index)
	{
			/*recorrer el árbol a la inversa desde nodoLuz hasta la raiz
			guardar el recorrido en una lista auxiliar de nodos de transformación
			invertir la lista auxiliar
			recorrer la lista auxiliar multiplicando las matrices en una matriz auxiliar
			obtener la posición de la luz a partir de la matriz auxiliar
			posicionar y activar la luz en la librería gráfica*/
	}

	c_rootNode.Draw();
}