#include "Roland.h"

int main()
{
	Roland motorGrafico(Rol::OpenGL, Rol::WindowData{ 800, 600, "Default title", false, false });

	Mesh* entity = motorGrafico.GetGraphicEngine()->CreateMesh("fakeMesh.obj", "Assets/container.jpg");
	Node* node = motorGrafico.GetGraphicEngine()->CreateNode(motorGrafico.GetGraphicEngine()->GetRootNode(), entity);

	motorGrafico.GetGraphicEngine()->StartLoop();
	
}