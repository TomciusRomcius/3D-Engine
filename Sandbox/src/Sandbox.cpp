#include <iostream>
#include "enpch.h"
#include "Engine.h"

class Sandbox : public Engine3D::Application
{
public:
	Sandbox(Engine3D::RenderAPI api)
	{
		Initialize(api);
	}
	void Start() override {
		using namespace Engine3D;
		auto obj = new Object();
		obj->AddComponent<Transform>();
		obj->AddComponent<Mesh>();
		obj->AddComponent<MeshRenderer>();
		obj->GetComponent<Mesh>().LoadModel("../Models/Cube.obj");
		obj->GetComponent<MeshRenderer>().texture = std::make_unique<Texture>("../Textures/brick.jpg");
	}

	void Update() override {
	}
};

int main()
{
	auto app = Sandbox(Engine3D::RenderAPI::OpenGL);
	app.Run();
}
