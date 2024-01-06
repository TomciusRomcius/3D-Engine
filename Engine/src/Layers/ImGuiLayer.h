#pragma once
#include "Core/Layer.h"
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "RendererLayer.h"
#include "Components/Mesh.h"
#include "Components/MeshRenderer.h"
#include "Components/Transform.h"
namespace Engine3D
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer(std::string name)
			: Layer(name)
		{ }
		~ImGuiLayer()
		{ }
		void OnAttach() override
		{
			IMGUI_CHECKVERSION();
			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO(); (void)io;
			ImGui::StyleColorsDark();
			ImGui_ImplGlfw_InitForOpenGL(m_WINDOW, true);
			ImGui_ImplOpenGL3_Init("#version 330");
			io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		}
		void OnDetach()
		{
			std::cout << "ImGuiLayer detached" << std::endl;
		}
		void Update() override
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
		void OnEvent(Event* event, EventType eventType)
		{
			if (eventType == EventType::MouseButtonEvent)
			{
				event->StopPropagation();
			}
		}

		void RenderHierarchy()
		{
			ImGui::Begin("Scene Hierarchy");
			auto& objects = SceneManager::CurrentScene().namedObjects;
			for (auto& object : objects)
			{
				if (ImGui::Button(object.first.c_str(), ImVec2(ImGui::GetContentRegionAvail().x, 0)))
				{
					m_SelectedObject = object.second;
				}
			}
			ImGui::End();
		}

		void RenderInspector()
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
			}
			ImGui::End();
		}
	private:
		Object* m_SelectedObject = nullptr;
		RendererLayer* m_RendererLayer = nullptr;
	};
}