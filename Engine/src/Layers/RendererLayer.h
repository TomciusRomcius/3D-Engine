#pragma once
#include "Core/Layer.h"
#include "Core/FrameBuffer.h"
#include "Core/SceneManager.h"
#include "Core/BufferElement.h"
#include "Core/Program.h"
#include "Core/VBO.h"
#include "Core/EBO.h"
#include "Core/VertexArray.h"
#include "Core/ECS/ComponentManager.h"
#include "Components/Transform.h"
#include "Components/Mesh.h"
#include "Components/MeshRenderer.h"
#include "Core/Input.h"

namespace Engine3D
{
	struct ComponentTest : public IComponent
	{
		void Start() override
		{
			Input::AddMousePressCallback(GLFW_MOUSE_BUTTON_LEFT, []() {
				std::cout << "Mouse 1 pressed" << std::endl;
			});
			Input::AddMousePressCallback(GLFW_MOUSE_BUTTON_RIGHT, []() {
				std::cout << "Mouse 2 pressed" << std::endl;
			});
			Input::AddKeyPressCallback(GLFW_KEY_A, []() {
				std::cout << "W pressed" << std::endl;
			});
		}
		void Update() override
		{
		}

	};

	static std::vector<glm::vec3> vertices = {
		glm::vec3(-1.0f, 1.0f, 0.0f),  // Top Left
		glm::vec3(1.0f, 1.0f, 0.0f),   // Top Right
		glm::vec3(1.0f, -1.0f, 0.0f),  // Bottom Right
		glm::vec3(-1.0f, -1.0f, 0.0f)  // Bottom Left
	};

	static std::vector<unsigned int> indices = {
		0, 1, 2,    // First Triangle
		2, 3, 0     // Second Triangle
	};

	static std::vector<glm::vec2> texCoords = {
		glm::vec2(0.0f, 0.0f), // Bottom Left
		glm::vec2(1.0f, 0.0f), // Bottom Right
		glm::vec2(1.0f, 1.0f), // Top Right
		glm::vec2(0.0f, 1.0f)  // Top Left
	};

	class RendererLayer : public Layer
	{
	public:
		RendererLayer(std::string name)
			: Layer(name)
		{
			auto vertBuffer = BufferElement(vertices.data(), BufferDataType::Float, vertices.size(), 3, false);
			auto texBuffer = BufferElement(texCoords.data(), BufferDataType::Float, texCoords.size(), 2, false);
			// void* data,
			std::vector<BufferElement> buffers = { vertBuffer, texBuffer };
			m_VBO = std::make_unique<VBO>(buffers);
			m_VAO = std::make_unique<VertexArray>(buffers);
			m_EBO = std::make_unique<EBO>(indices);
			m_Program = std::make_unique<Program>(
				new Shader(GL_VERTEX_SHADER, "framebuffer.vert"),
				new Shader(GL_FRAGMENT_SHADER, "framebuffer.frag"));
			m_Program->UseProgram();
			glUniform1i(glGetUniformLocation(m_Program->Id(), "screenTexture"), 0);
			m_Framebuffer = std::make_unique<Framebuffer>();
		}
		~RendererLayer()
		{ }
		void OnAttach() override
		{
			SceneManager::Initialize();
			std::cout << "RendererLayer attached" << std::endl;
			Object* obj = new Object("Object");
			obj->AddComponent<MeshRenderer>();
			obj->AddComponent<Transform>();
			obj->GetComponent<Transform>().position.z = -5;
			obj->GetComponent<Transform>().rotation.y = 45;
			obj->AddComponent<Mesh>();
			obj->AddComponent<ComponentTest>();
			obj->GetComponent<Mesh>().LoadModel("Cube.obj");
		}
		void OnDetach()
		{
			std::cout << "RendererLayer detached" << std::endl;
		}
		void Update() override
		{
			// Render to framebuffer
			m_Framebuffer->Bind();
			m_VBO->Bind();
			m_VAO->Bind();
			m_EBO->Bind();
			m_Program->UseProgram();
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

			ComponentManager::Update();
			SceneCamera::Move();

			m_Framebuffer->Unbind();
		}
		void OnEvent(Event* event, EventType eventType)
		{
			Input::OnEvent(event, eventType);
			event->StopPropagation();
		}

		inline unsigned int GetFrameBufferTextureID() 		{
			return m_Framebuffer->TextureId();
		}
	private:
		std::unique_ptr<Framebuffer> m_Framebuffer;
		std::unique_ptr<VBO> m_VBO;
		std::unique_ptr<EBO> m_EBO;
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<Program> m_Program;
	};
}
