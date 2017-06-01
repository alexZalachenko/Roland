#include "Roland.h"
#include "Mesh.h"
#include "Node.h"
#include "Transform.h"
#include "OpenGLEngine.h"
#include "PerspectiveCamera.h"

int main()
{
	Roland t_roland(Rol::OpenGL, Rol::WindowData{ 800, 600, "Default title", false, false });
	IGraphicEngine* motorGrafico = t_roland.GetGraphicEngine();

	//mesh at the root
	//Mesh*	t_entity = motorGrafico->CreateMesh("Assets/Meshes/cubo.obj");
	Mesh*	t_entity = motorGrafico->CreateMesh("fakeMesh.obj");
	Node*	entityNode = motorGrafico->CreateNode(motorGrafico->GetRootNode(), t_entity);

	Transform* t_transform = motorGrafico->CreateTransform();
	t_transform->Rotate(45, 0, 1, 0);
	Node*	t_transformNode = motorGrafico->CreateNode(motorGrafico->GetRootNode(), t_transform);

	Transform* t_transform1 = motorGrafico->CreateTransform();
	t_transform1->Translate(0, 0, 4);
	Node*	t_transformNode1 = motorGrafico->CreateNode(t_transformNode, t_transform1);

	Camera* t_camera = motorGrafico->CreatePerspectiveCamera(100, 0.1f, 45, 800, 600);
	Node*	t_cameraNode = motorGrafico->CreateNode(t_transformNode1, t_camera);
	motorGrafico->SetActiveCamera(t_cameraNode);

	motorGrafico->StartLoop();
}