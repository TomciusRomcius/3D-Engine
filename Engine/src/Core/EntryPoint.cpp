#include "enpch.h"
#include <iostream>
#include "Application.h"

using namespace Engine3D;

int main()
{
	Application* app = new Application();
	app->Initialize(RenderAPI::OpenGL);
	app->Run();
	return 0;
}
