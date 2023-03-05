#include <iostream>
#include "enpch.h"
#include "Core/Application.h"


class Sandbox : public  Engine3D::Application
{
	
	void Start() override
	{
		using namespace Engine3D;

		auto o = new Object();

		o->AddComponent<Transform>();
		o->AddComponent<Mesh>();
		o->AddComponent<MeshRenderer>();
		o->GetComponent<Mesh>().LoadModel("../Models/Cube.obj");
		o->GetComponent<Transform>().position = { 0, 0, 0 };
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
