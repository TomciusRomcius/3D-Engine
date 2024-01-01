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

namespace Engine3D
{
	class ENGINE_API OpenGLWindow : public IWindow
	{
	public:
		OpenGLWindow() {}
		void Initialize(std::function<void()> start, std::function<void()> update) override;
		void MainLoop(std::function<void()> start, std::function<void()> update);
	protected:
		GLFWwindow* WINDOW;
		void RenderUI();
	};


}
