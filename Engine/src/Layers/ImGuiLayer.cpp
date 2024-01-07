#include "enpch.h"
#include "ImGuiLayer.h"

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
	RenderHierarchy();
	RenderInspector();
	ImGui::Begin("Asset manager");
	ImGui::End();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Engine3D::ImGuiLayer::OnEvent(Event* event, EventType eventType)
{
	if (eventType == EventType::MouseButtonEvent)
	{
		event->StopPropagation();
	}
}

void Engine3D::ImGuiLayer::RenderHierarchy()
{
	ImGui::Begin("Scene Hierarchy");
	auto& objects = sceneManager.CurrentScene().namedObjects;
	for (auto& object : objects)
	{
		if (ImGui::Button(object.first.c_str(), ImVec2(ImGui::GetContentRegionAvail().x, 0)))
		{
			m_SelectedObject = object.second;
		}
	}
	ImGui::End();
}

void Engine3D::ImGuiLayer::RenderInspector()
{
	ImGui::Begin("Inspector");

	if (m_SelectedObject != nullptr)
	{
		ImGui::Text(std::to_string(m_SelectedObject->Id()).c_str());
		auto& transform = m_SelectedObject->GetComponent<Transform>();
		auto& meshRenderer = m_SelectedObject->GetComponent<MeshRenderer>();
		auto& mesh = m_SelectedObject->GetComponent<Mesh>();
		if (ImGui::TreeNode("Transform"))
		{
			ImGui::DragFloat3("Position", &transform.position.x, 0.1f);
			ImGui::DragFloat3("Rotation", &transform.rotation.x, 0.1f);
			ImGui::DragFloat3("Scale", &transform.scale.x, 0.1f);
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("Mesh"))
		{
			std::string loadedModel = mesh.GetLoadedModel();
			if (loadedModel != "")
			{
				ImGui::Text(("Loaded model: " + loadedModel).c_str());
			}
			else
			{
				ImGui::Text("No model loaded");
			}
			ImGui::Button("Load model");
			ImGui::TreePop();
		}

		static bool open = true;

		if (ImGui::Button("Create component")) open = !open;
		if (open)
		{
			const int MAX_NAME_LENGTH = 50;
			static char name[MAX_NAME_LENGTH] = "";
			ImGui::InputText("Component name", name, MAX_NAME_LENGTH);
			ImGui::Text("Entered text: %s", name);
			if (ImGui::Button("Create"))
			{
				std::string sName = convertCharToString(name, MAX_NAME_LENGTH);
				CreateComponent(sName);
			}
		}
	}
	ImGui::End();
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
