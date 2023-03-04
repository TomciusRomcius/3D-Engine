#pragma once

#include <chrono>

#include "Event.h"
#include "DebugLayer.h"
#include "enpch.h"

#include "VBO.h"
#include "Shader.h"
#include "Program.h"

#include "Time.h"

#include "ObjectSystem.h"
#include "../Components/IComponent.h"
#include "../Components/Transform.h"
#include "../Components/Mesh.h"
#include "../Components/MeshRenderer.h"

namespace Engine3D
{
	class ENGINE_API ApplicationLayer
	{
	public:
		static void Start();
		static void MainLoop();
		virtual void CreateWindow() = 0;
	private:
		static GLFWwindow* WINDOW;
		static void RenderUI();
	};
}