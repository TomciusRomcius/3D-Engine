#pragma once
#include "Core/Layer.h"
#include "Core/FrameBuffer.h"
#include "Core/BufferElement.h"
#include "Core/Program.h"
#include "Core/VBO.h"
#include "Core/EBO.h"
#include "Core/VertexArray.h"
#include "Core/Input.h"

namespace Engine3D
{

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
		RendererLayer(std::string name);
		~RendererLayer()
		{ }
		void OnAttach() override;
		void OnDetach();
		void Update() override;
		void OnEvent(Event* event, EventType eventType);

		inline unsigned int GetFrameBufferTextureID() 		{
			return m_Framebuffer->TextureId();
		}
	private:
		//std::map<std::string, ComponentData> componentDLLS;
		std::unique_ptr<Framebuffer> m_Framebuffer;
		std::unique_ptr<VBO> m_VBO;
		std::unique_ptr<EBO> m_EBO;
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<Program> m_Program;
	};
}
