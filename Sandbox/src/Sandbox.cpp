#include <iostream>
#include "enpch.h"
#include "Engine.h"


class Sandbox : public Engine3D::Application
{
	
	void Start() override
	{
		using namespace Engine3D;
		auto o = new Object();
		o->AddComponent<Transform>();
		o->AddComponent<Mesh>();
		o->AddComponent<MeshRenderer>();
		o->GetComponent<MeshRenderer>().color = { .5f, 1, 0 };
		o->GetComponent<Mesh>().LoadModel("../Models/Cube.obj");
		o->GetComponent<MeshRenderer>().texture = std::make_unique<Texture>("../Textures/brick.jpg");

	}
	void Update() override
	{

	}
	
};

int main()
{
	Sandbox* app = new Sandbox();
	app->Initialize();
}
