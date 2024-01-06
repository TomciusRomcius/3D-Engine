#pragma once
#include "../Core/LayerSystem.h"
#include "Event.h"

namespace Engine3D
{
    class EventSystem
    {
    public:
        static void Initialize(GLFWwindow* WINDOW, LayerSystem* layerSystem);

    private:
        // Callbacks
        static GLFWwindow* m_WINDOW;
        static LayerSystem* m_LayerSystem;
        static void m_KeyCallCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void m_MouseCursorCallback(GLFWwindow* window, double xPos, double yPos);
        static void m_MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	};
}

