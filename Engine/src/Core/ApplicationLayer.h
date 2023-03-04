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
		void Start();
		void MainLoop();
	private:
		GLFWwindow* WINDOW;
		void RenderUI();
	};
	extern ENGINE_API Engine3D::ApplicationLayer* CreateApplication();


}
