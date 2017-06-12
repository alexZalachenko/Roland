#include "Roland.h"
#include "Mesh.h"
#include "Node.h"
#include "Transform.h"
#include "OpenGLEngine.h"
#include "PerspectiveCamera.h"
#include "FPSCamera.h"

int main()
{
	//se inicia el motor
	Roland t_roland(Rol::OpenGL, Rol::WindowData{ 800, 600, "Default title", false, false });
	IGraphicEngine* motorGrafico = t_roland.GetGraphicEngine();

	//se crea una malla grafica con datos por programa
	//Mesh*	t_entity = motorGrafico->CreateMesh("Assets/Meshes/cubeTextured.obj", "Assets/Meshes/cubeTexture.png");
	Mesh*	t_entity = motorGrafico->CreateMesh("fakeMesh.obj", "Assets/container.jpg");
	t_entity->DisplayMeshData();
	Node*	entityNode = motorGrafico->CreateNode(motorGrafico->GetRootNode(), t_entity);

	//se crea una transformacion para posicionar la camara
	Transform* t_transform = motorGrafico->CreateTransform();
	t_transform->Translate(0, 0, -4);
	Node*	t_transformNode = motorGrafico->CreateNode(motorGrafico->GetRootNode(), t_transform);

	//se crea una camara y se le añade la transformacion anterior
	//Camera* t_camera = motorGrafico->CreatePerspectiveCamera(100, 0.1f, 45, 800, 600);
	//FPSCamera* t_camera = motorGrafico->CreateFPSCamera(100, 0.1f, 45, 800, 600);
	//Node*	t_cameraNode = motorGrafico->CreateNode(t_transformNode, t_camera);
	//motorGrafico->SetActiveCamera(t_cameraNode);

	//se inicia el bucle de juego
	motorGrafico->StartLoop();
}