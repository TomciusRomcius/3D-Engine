#pragma once
#include "Core/Layer.h"
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "../RendererLayer.h"
#include "ObjectSystem.h"
#include "Components/Transform.h"
#include "Components/MeshRenderer.h"
#include "Components/Mesh.h"
#include "Hierarchy.h"

namespace Engine3D
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer(std::string name);
		~ImGuiLayer();
		void OnAttach() override;
		void OnDetach();
		void Update() override;
		void OnEvent(Event* event, EventType eventType);
		void RenderHierarchy();
		void RenderInspector();
	private:
		RendererLayer* m_RendererLayer = nullptr;
		std::vector<std::unique_ptr<Section>> m_Sections;
		void CreateComponent(std::string name);
		std::string convertCharToString(char* c, int size);
	};
}