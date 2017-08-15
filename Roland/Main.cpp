#include "Roland.h"
#include "Mesh.h"
#include "Node.h"
#include "Transform.h"
#include "IGraphicEngine.h"
#include <iostream>
#include "Camera.h"
#include "Light.h"
#include "FPSCamera.h"

int main()
{
	//se inicia el motor
	Roland t_roland(Rol::OpenGL, Rol::WindowData{ 800, 600, "Default title", false, false });
	IGraphicEngine* motorGrafico = t_roland.GetGraphicEngine();
	motorGrafico->CreateNewProgram("Assets/Shaders/VertexShaderAdvancedLightning.txt", "Assets/Shaders/FragmentShaderAdvancedLightning.txt", "newProgram");

	//se carga un modelo 3D
	Mesh* t_mesh = motorGrafico->CreateMesh("Assets/Meshes/plane.obj");
	t_mesh->DisplayEntityData("");

	std::cin.get();
}