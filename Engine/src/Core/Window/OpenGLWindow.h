#pragma once

#include <chrono>

#include "Events/EventSystem.h"
#include "../DebugLayer.h"
#include "enpch.h"

#include "../VBO.h"
#include "../VertexArray.h"
#include "../Shader.h"
#include "../Program.h"
#include "../FrameBuffer.h"

#include "Time.h"

#include "../ECS/ObjectSystem.h"
#include "../../Components/IComponent.h"
#include "../../Components/Transform.h"
#include "../../Components/Mesh.h"
#include "../../Components/MeshRenderer.h"

#include "../Log.h"
#include "IWindow.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "../LayerSystem.h"
#include "../../Layers/ImGuiLayer.h"
#include "../../Layers/RendererLayer.h"

namespace Engine3D
{
	class ENGINE_API OpenGLWindow : public IWindow
	{
	public:
		OpenGLWindow() {}
		void Initialize() override;
		void MainLoop();
		virtual void Start() {};
		virtual void Update() {};
		virtual void UIUpdate() {};
	protected:
		GLFWwindow* WINDOW;
		void RenderUI(unsigned int framebufferTexture);
		std::unique_ptr<LayerSystem> m_LayerSystem;
		unsigned int m_framebufferTexture;
		ImGuiContext* m_imGuiContext;
	};


}
