#pragma once

#include <chrono>

#include "Event.h"
#include "DebugLayer.h"
#include "../pch.h"

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
	class ApplicationLayer
	{
	public:
		static void Start();
		static void MainLoop();
	private:
		static GLFWwindow* WINDOW;
		static void RenderUI();
	};
}