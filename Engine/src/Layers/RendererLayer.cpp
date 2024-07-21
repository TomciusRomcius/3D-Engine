#include "enpch.h"
#include "RendererLayer.h"
#include "DLL.h"
#include "Components/Transform.h"
#include "Components/Mesh.h"
#include "Components/MeshRenderer.h"

void Engine3D::RendererLayer::Update()
{
	// Render to framebuffer
	m_Framebuffer->Bind();
	glDisable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT);
	componentManager.Update();

	m_Framebuffer->Unbind();
	m_VBO->Bind();
	m_VAO->Bind();
	m_EBO->Bind();
	m_Program->UseProgram();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

Engine3D::RendererLayer::RendererLayer(std::string name)
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

void Engine3D::RendererLayer::OnAttach()
{
	Object* obj = new Object("Cube");
	obj->AddComponent<Transform>();
	obj->AddComponent<Mesh>();
	obj->AddComponent<MeshRenderer>();
	obj->GetComponent<Transform>().position.z = -15;
	obj->GetComponent<Transform>().rotation.y = 45;
	obj->GetComponent<Mesh>().LoadModel("Cube.obj");
}

void Engine3D::RendererLayer::OnDetach()
{
	std::cout << "RendererLayer detached" << std::endl;
}

void Engine3D::RendererLayer::OnEvent(Event* event, EventType eventType)
{
	Input::OnEvent(event, eventType);
	event->StopPropagation();
}
