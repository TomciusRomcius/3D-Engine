#pragma once

#include <chrono>

#include "../Event.h"
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
		unsigned int m_framebufferTexture;
		ImGuiContext* m_imGuiContext;
	};


}
