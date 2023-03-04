#include <iostream>
#include "enpch.h"
#include "Core/ApplicationLayer.h"


#pragma comment(lib, "Engine.lib")

int main()
{
	auto app = Engine3D::CreateApplication();
	app->Start();
}
Engine3D::ApplicationLayer* Engine3D::CreateApplication()
{
	return new ApplicationLayer();
}