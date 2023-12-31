#include <iostream>
#include "enpch.h"
#include "Engine.h"
#include "Components/IComponent.h"
#include "Components/Transform.h"

struct CustomComponent : public Engine3D::IComponent
{
	void Start() override {

	}
	void Update() override {
		auto& scene = Engine3D::SceneManager::CurrentScene();
		auto obj = scene.FindObjectByName("Cube 2");
		if (obj == nullptr) return;
		obj->GetComponent<Engine3D::Transform>().position.x += 0.01f;
	}
};

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

		auto obj2 = new Object("Cube 2");
		obj2->AddComponent<Transform>();
		obj2->AddComponent<Mesh>();
		obj2->AddComponent<MeshRenderer>();
		obj2->GetComponent<Mesh>().LoadModel("../Models/Cube.obj");
		obj2->GetComponent<MeshRenderer>().texture = std::make_unique<Texture>("../Textures/brick.jpg");
		obj2->GetComponent<Transform>().position = glm::vec3(0, 0, -8);

		obj2->AddComponent<CustomComponent>();
	}

	void Update() override {
	}
};

int main()
{
	auto app = Sandbox(Engine3D::RenderAPI::OpenGL);
	app.Run();
}
