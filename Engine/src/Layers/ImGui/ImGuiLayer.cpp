#include "enpch.h"
#include "ImGuiLayer.h"
#include "Inspector.h"

Engine3D::ImGuiLayer::ImGuiLayer(std::string name)
	: Layer(name)
{ }

Engine3D::ImGuiLayer::~ImGuiLayer()
{ }

void Engine3D::ImGuiLayer::OnAttach()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(m_WINDOW, true);
	ImGui_ImplOpenGL3_Init("#version 330");
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	// Styling
	ImGuiStyle& style = ImGui::GetStyle();

	m_Sections.push_back(std::make_unique<Hierarchy>());
	m_Sections.push_back(std::make_unique<Inspector>());

	for (auto& section : m_Sections)
	{
		section->Start();
	}
}

void Engine3D::ImGuiLayer::OnDetach()
{
	std::cout << "ImGuiLayer detached" << std::endl;
}

void Engine3D::ImGuiLayer::Update()
{
	if (m_RendererLayer == nullptr)
	{
		for (auto& layer : *m_OtherLayers)
		{
			if (layer->GetName() == "RendererLayer")
			{
				m_RendererLayer = (RendererLayer*)layer;
				break;
			}
		}
	}
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
	ImGui::SetNextWindowSize(ImVec2(1024, 576), ImGuiCond_FirstUseEver);
	ImGui::Begin("Viewport");
	ImGui::Image((void*)m_RendererLayer->GetFrameBufferTextureID(), ImVec2(1024, 576), ImVec2(0, 1), ImVec2(1, 0));
	ImGui::End();
	
	for (auto& section : m_Sections)
	{
		section->Update();
	}

	ImGui::Begin("Asset manager");
	ImGui::End();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Engine3D::ImGuiLayer::OnEvent(Event* event, EventType eventType)
{
	for (auto& section : m_Sections)
	{
		section->OnEvent(event, eventType);
	}
}

void Engine3D::ImGuiLayer::RenderHierarchy()
{
}

void Engine3D::ImGuiLayer::RenderInspector()
{
	
}

void Engine3D::ImGuiLayer::CreateComponent(std::string name)
{
	// Convert to string:
	EN_TRACE("Adding component: {0}", name);
}

std::string Engine3D::ImGuiLayer::convertCharToString(char* c, int size)
{
	int i = 0;
	std::string s = "";
	for (i = 0; i < size; i++)
	{
		s += c[i];
	}
	return s;
}
