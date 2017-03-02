#include "Roland.h"

int main()
{
	Roland motorGrafico(Rol::OpenGL);
	motorGrafico.InitEngine(Rol::WindowData{ 800, 600, "Default title", false, false });
	motorGrafico.StartRenderLoop();
}