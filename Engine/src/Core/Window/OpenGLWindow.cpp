#include "enpch.h"
#include "OpenGLWindow.h"

std::vector<glm::vec3> vertices = {
	glm::vec3(-1.0f, 1.0f, 0.0f),  // Top Left
	glm::vec3(1.0f, 1.0f, 0.0f),   // Top Right
	glm::vec3(1.0f, -1.0f, 0.0f),  // Bottom Right
	glm::vec3(-1.0f, -1.0f, 0.0f)  // Bottom Left
};

std::vector<unsigned int> indices = {
	0, 1, 2,    // First Triangle
	2, 3, 0     // Second Triangle
};

std::vector<glm::vec2> texCoords = {
	glm::vec2(0.0f, 1.0f), // Top Left
	glm::vec2(1.0f, 1.0f), // Top Right
	glm::vec2(1.0f, 0.0f), // Bottom Right
	glm::vec2(0.0f, 0.0f)  // Bottom Left
};

namespace Engine3D
{
	void OpenGLWindow::Initialize(std::function<void()> start, std::function<void()> update)
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
		OpenGLWindow::WINDOW = glfwCreateWindow(1280, 720, "OpenGL 3D Modeler", nullptr, nullptr);

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
		
		// Initialize event system and a debugger
		Event::Initialize(WINDOW);
		DebugLayer::Initialize(WINDOW);

		// Important to call before creating first object

		// Register primary components
		ComponentManager::GetInstance().RegisterComponent<Transform>();
		ComponentManager::GetInstance().RegisterComponent<Mesh>();
		ComponentManager::GetInstance().RegisterComponent<MeshRenderer>();

		MainLoop(start, update);
	}

	void OpenGLWindow::MainLoop(std::function<void()> start, std::function<void()> update)
	{
		// Time variables for calculating delta 
		std::chrono::high_resolution_clock::time_point t1;
		std::chrono::high_resolution_clock::time_point t2;

		std::chrono::high_resolution_clock::time_point s = std::chrono::high_resolution_clock::now();
		std::chrono::high_resolution_clock::time_point e;

		// Variables for calculating fps

		int frames = 0;
		double sT = glfwGetTime();

		auto framebuffer = Framebuffer();
		auto vertBuffer = BufferElement(vertices.data(), BufferDataType::Float, vertices.size(), 3, false);
		auto texBuffer = BufferElement(texCoords.data(), BufferDataType::Float, texCoords.size(), 2, false);
		auto buffers = std::vector<BufferElement>{ vertBuffer, texBuffer };

		auto quadVBO = VBO(buffers);
		auto quadEBO = EBO(indices);
		auto program = new Program(new Shader(GL_VERTEX_SHADER, "framebuffer.vert"), new Shader(GL_FRAGMENT_SHADER, "framebuffer.frag"));
		program->UseProgram();
		glUniform1i(glGetUniformLocation(program->Id(), "screenTexture"), 0);
		SceneManager::Initialize();
		start();
		while (!glfwWindowShouldClose(WINDOW))
		{
			update();
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
			Time::DeltaTime = (float)(t1 - t2).count() / 1000000000.f;

			// Render to framebuffer
			framebuffer.Bind();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glClearColor(0, 0, 0.1, 1);
			glEnable(GL_DEPTH_TEST);
			ComponentManager::Update();
			SceneCamera::Move();

			// RenderUI();

			// Render framebuffer to screen
			framebuffer.Unbind();
			glClear(GL_COLOR_BUFFER_BIT);
			glDisable(GL_DEPTH_TEST);
			program->UseProgram();
			quadVBO.Bind();
			quadEBO.Bind();
			glBindTexture(GL_TEXTURE_2D, framebuffer.TextureId());
			glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);
			
			glfwSwapBuffers(WINDOW);
			glfwPollEvents();
		}
	}
	void OpenGLWindow::RenderUI()
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
