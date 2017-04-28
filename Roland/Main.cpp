#include "Roland.h"
#include "Mesh.h"
#include "Node.h"
#include "OpenGLEngine.h"

int main()
{
	Roland motorGrafico(Rol::OpenGL, Rol::WindowData{ 800, 600, "Default title", false, false });

	Mesh* entity = motorGrafico.GetGraphicEngine()->CreateMesh("Assets/Meshes/untitled.obj");

	Node* node = motorGrafico.GetGraphicEngine()->CreateNode(motorGrafico.GetGraphicEngine()->GetRootNode(), entity);

	motorGrafico.GetGraphicEngine()->StartLoop();
	
}