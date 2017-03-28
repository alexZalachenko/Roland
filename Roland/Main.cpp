#include "Roland.h"

int main()
{
	Roland motorGrafico(Rol::OpenGL, Rol::WindowData{ 800, 600, "Default title", false, false });

	Mesh* mesh = motorGrafico.GetGraphicEngine()->CreateMesh("fakeMesh");
	Node* node = motorGrafico.GetGraphicEngine()->CreateNode(motorGrafico.GetGraphicEngine()->GetRootNode(), mesh);

	motorGrafico.GetGraphicEngine()->StartLoop();
	
}