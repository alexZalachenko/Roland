#include "OpenGLEngine.h"
#include <GLFW/glfw3.h>//for creating a window and reading users' input
#include <iostream>
#include "CallbackFunctions.h"
#include <fstream>
#include "Node.h"
#include "IEntity.h"
#include "IGraphicEngine.h"
#include "Transform.h"
#include "Camera.h"
#include "Light.h"
#include "Mesh.h"
#include "MeshResource.h"
#include "ResourcesManager.h"

OpenGLEngine::OpenGLEngine()
	: c_window(nullptr),
	IGraphicEngine(Rol::OpenGL)
{
	Init();
}

OpenGLEngine::~OpenGLEngine()
{
	//delete lights delete cameras
	/*glDeleteShader(c_vertexShader);
	glDeleteShader(c_fragmentShader);*/
	Terminate();
}

			/*Methods related to engine's configuration*/
void		OpenGLEngine::SetupEngine(Rol::WindowData p_windowData)
{
	Init();
	CreateWindow(p_windowData);
	InitGlew();
	InitCallbacks();
	c_shaderProgram = glCreateProgram();
	LinkShader(CompileShader("VertexShader.txt", GL_VERTEX_SHADER));
	LinkShader(CompileShader("FragmentShader.txt", GL_FRAGMENT_SHADER));
}

void		OpenGLEngine::Terminate()
{
	glfwTerminate();
}

void		OpenGLEngine::Init()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void		OpenGLEngine::CreateWindow(Rol::WindowData p_windowData)
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
}

void		OpenGLEngine::InitGlew()
{
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		exit(-1);
	}
}

void		OpenGLEngine::InitCallbacks()
{
	glfwSetKeyCallback(c_window, OpenGLCallbacks::key_callback);
}

GLuint		OpenGLEngine::CompileShader(const GLchar* p_shaderFile, unsigned short p_shaderType)
{
	//read the shader from the specified file
	std::string t_shaderCode;
	std::ifstream t_shaderStream(p_shaderFile, std::ios::in);
	if (t_shaderStream.is_open()){
		std::string Line = "";
		while (getline(t_shaderStream, Line))
			t_shaderCode += "\n" + Line;
		t_shaderStream.close();
	}
	else{
		std::cout << "Impossible to open " << p_shaderFile << std::endl;
		exit(-1);
	}

	char const * t_shaderCodeConverted = t_shaderCode.c_str();
	GLuint r_shaderID = glCreateShader(p_shaderType);//create a empty shader of the passed type
	glShaderSource(r_shaderID, 1, &t_shaderCodeConverted, NULL);//set the source code to the created shader
	glCompileShader(r_shaderID);
	// Check for compile time errors
	GLint t_success;
	GLchar t_infoLog[512];
	glGetShaderiv(r_shaderID, GL_COMPILE_STATUS, &t_success);//set the shader to be queried and what to query about. Store the result code
	if (!t_success)
	{
		glGetShaderInfoLog(r_shaderID, 512, NULL, t_infoLog);//store the query info in t_infoLog
		std::cout << "ERROR COMPILING SHADER " << p_shaderFile << " COMPILATION_FAILED\n" << t_infoLog << std::endl;
		exit(-1);
	}
	return r_shaderID;
}

void		OpenGLEngine::LinkShader(GLuint p_shader)
{
	glAttachShader(c_shaderProgram, p_shader);
	glLinkProgram(c_shaderProgram);
	GLint t_success;
	GLchar t_infoLog[512];
	glGetProgramiv(c_shaderProgram, GL_LINK_STATUS, &t_success);
	if (!t_success) {
		glGetProgramInfoLog(c_shaderProgram, 512, NULL, t_infoLog);
		std::cout << "ERROR LINKING SHADER. LINKING_FAILED\n" << t_infoLog << std::endl;
		exit(-1);
	}
	glDeleteShader(p_shader);
}

void		OpenGLEngine::StartLoop()
{
	while (!glfwWindowShouldClose(c_window))
	{
		// Check if any events have been activated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Clear the colorbuffer
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//use vertex shader
		glUseProgram(c_shaderProgram);

		//draw the scene tree
		Draw();

		// Swap the screen buffers
		glfwSwapBuffers(c_window);
	}
}

			/*Methods related to engine's client functionality*/
Node*		OpenGLEngine::CreateNode(Node* p_father, IEntity* p_IEntity)
{
	Node* t_newNode = new Node(p_father, p_IEntity);
	return t_newNode;
}

Node*		OpenGLEngine::CreateNode()
{
	Node* t_newNode = new Node();
	return t_newNode;
}

Transform*	OpenGLEngine::CreateTransform()
{
	Transform* t_newTransform = new Transform;
	return t_newTransform;
}

Camera*		OpenGLEngine::CreateCamera()
{
	//TODO
	return nullptr;
}

Light*		OpenGLEngine::CreateLight()
{
	//TODO
	Light* t_newLight = new Light;
	return t_newLight;
}

Mesh*		OpenGLEngine::CreateMesh(std::string p_file)
{
	Mesh* r_newMesh = new Mesh;
	//get the resource from the resources manager
	Resource* t_resource = c_resourcesManager.GetResource(p_file);
	//set it to the new created mesh
	if (t_resource != nullptr)
		r_newMesh->SetMeshResource(dynamic_cast<MeshResource*>(t_resource));
	return r_newMesh;
}

/*delete mesh from the resources manager. If the mesh is wanted to use again it will must be loaded*/
void		OpenGLEngine::DeleteMesh(std::string p_file)
{
	//TODO
}

void		OpenGLEngine::RegisterLightNode(Node* p_lightNode)
{
	if (p_lightNode != nullptr)
		c_lights.push_back(p_lightNode);
}

void		OpenGLEngine::RegisterCameraNode(Node* p_cameraNode)
{
	if (p_cameraNode != nullptr)
		c_cameras.push_back(p_cameraNode);
}

void		OpenGLEngine::Draw()
{
	//TODO
	for (size_t t_index = 0; t_index < c_lights.size(); ++t_index)
	{
			/*recorrer el árbol a la inversa desde nodoLuz hasta la raiz
			guardar el recorrido en una lista auxiliar de nodos de transformación
			invertir la lista auxiliar
			recorrer la lista auxiliar multiplicando las matrices en una matriz auxiliar
			obtener la posición de la luz a partir de la matriz auxiliar
			posicionar y activar la luz en la librería gráfica*/
	}

	/*nodoCamara = getCamaraActiva ();
	 recorrer el árbol a la inversa desde nodoCamara hasta la raiz
	 guardar el recorrido en una lista auxiliar de nodos de transformación
	 invertir la lista auxiliar
	 recorrer la lista auxiliar multiplicando las matrices en una matriz auxiliar
	 invertir la matriz auxiliar
	 cargar la matriz auxiliar en la matriz MODELVIEW de la librería gráfica */
	c_rootNode.Draw();
}