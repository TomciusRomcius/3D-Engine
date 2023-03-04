#include "enpch.h"
#include "ApplicationLayer.h"
#include "../Components/Transform.h"


void bra()
{

}
namespace Engine3D
{

	GLFWwindow* ApplicationLayer::WINDOW;
	void ApplicationLayer::Start()
	{
		// Initialize GLFW and GLEW, Create window, setup Key and Error callbacks
		if (!glfwInit())
		{
			std::cout << "Failed to initialize GLFW, exiting..." << std::endl;
			return;
		}
		
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

		// Create Window
		ApplicationLayer::WINDOW = glfwCreateWindow(1280, 720, "OpenGL 3D Modeler", nullptr, nullptr);

		if (WINDOW == nullptr)
		{
			std::cout << "Failed to create the window, exiting..." << std::endl;
			return;
		}
		glfwMakeContextCurrent(WINDOW);
		glViewport(0, 0, 1280, 720);
		if (glewInit() != GLEW_OK)
		{
			std::cout << "Failed to initialize GLEW, exiting..." << std::endl;
			return;
		}
		
		// Initialize ImGui

		
		// Initialize event system and a debugger
		Event::Initialize(WINDOW);
		DebugLayer::Initialize(WINDOW);

		// Important to call before creating first object
		Object::InitQueue();

		// Register primary components
		ComponentManager::GetInstance().RegisterComponent<Transform>();
		ComponentManager::GetInstance().RegisterComponent<Mesh>();
		ComponentManager::GetInstance().RegisterComponent<MeshRenderer>();

		ApplicationLayer::MainLoop();
	}

	void ApplicationLayer::MainLoop()
	{
		// Time variables for calculating delta 
		std::chrono::high_resolution_clock::time_point t1;
		std::chrono::high_resolution_clock::time_point t2;

		std::chrono::high_resolution_clock::time_point s = std::chrono::high_resolution_clock::now();
		std::chrono::high_resolution_clock::time_point e;

		Object* o = new Object();
		o->AddComponent<Transform>();
		o->AddComponent<Mesh>();
		o->AddComponent<MeshRenderer>();


		while (!glfwWindowShouldClose(WINDOW))
		{
			// My logic

			ComponentManager::Update();
			SceneCamera::Move();

			// Calculate elapsed time

			e = std::chrono::high_resolution_clock::now();
			Time::ElapsedTime = (float)(e - s).count() / 1000000000.f;

			// Calculate delta time

			t2 = t1;
			t1 = std::chrono::high_resolution_clock::now();
			Time::DeltaTime = (float)(t1 - t2).count() / 1000000000.f;

			// ImGui

			


			RenderUI();


			
			// GLFW

			glfwSwapBuffers(WINDOW);
			glClear(GL_COLOR_BUFFER_BIT);
			glfwPollEvents();




		}
	}
	void ApplicationLayer::RenderUI()
	{
		/*
		ImGui::Begin("Viewport");

		ImGui::End();
		ImGui::Begin("Properties");
		ImGui::End();
		ImGui::Begin("Hierarchy");
		ImGui::End();
		*/
	}
}
