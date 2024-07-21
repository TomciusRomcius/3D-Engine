#include "enpch.h"
#include "OpenGLWindow.h"

namespace Engine3D
{
	void OpenGLWindow::Initialize()
	{
		
		// Initialize GLFW and GLEW, Create window, setup Key and Error callbacks
		if (!glfwInit())
		{
			EN_ERROR("Failed to initialize GLFW, exiting...")
			return;
		}
		
		int versionminor = 3;
		int versionmajor = 3;

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, versionminor);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, versionmajor);

		// Create OpenGLWindow
		OpenGLWindow::WINDOW = glfwCreateWindow(1600, 900, "OpenGL 3D Modeler", nullptr, nullptr);

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
		glfwSetWindowAspectRatio(WINDOW, 16, 9);
		// Initialize event system and a debugger

		m_LayerSystem = std::make_unique<LayerSystem>(WINDOW);
		EventSystem::Initialize(WINDOW, m_LayerSystem.get());
		DebugLayer::Initialize(WINDOW);

		auto rendererLayer = new RendererLayer("RendererLayer");
		auto imGuiLayer = new ImGuiLayer("ImGuiLayer");
		m_LayerSystem->AttachLayer(rendererLayer);
		m_LayerSystem->AttachLayer(imGuiLayer);


		Start();
		MainLoop();
	}

	void OpenGLWindow::MainLoop()
	{
		// Time variables for calculating delta 
		std::chrono::high_resolution_clock::time_point t1;
		std::chrono::high_resolution_clock::time_point t2;

		std::chrono::high_resolution_clock::time_point s = std::chrono::high_resolution_clock::now();
		std::chrono::high_resolution_clock::time_point e;

		// Variables for calculating fps

		int frames = 0;
		double sT = glfwGetTime();

		while (!glfwWindowShouldClose(WINDOW))
		{
			glClearColor(0.0f, 0.05f, 0.3f, 1.0f);
			// Time calculations
			e = std::chrono::high_resolution_clock::now();
			Time::ElapsedTime = (float)(e - s).count() / 1000000000.f;
			double sN = glfwGetTime();
			frames++;
			if (sN - sT >= 1.0)
			{
				sT = sN;
				frames = 0;
			}

			t2 = t1;
			t1 = std::chrono::high_resolution_clock::now();
			Engine3D::Time::DeltaTime = (float)(t1 - t2).count() / 1000000000.f;

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			m_LayerSystem->Update();

			glfwSwapBuffers(WINDOW);
			glfwPollEvents();
		}
	}
}
