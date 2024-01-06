#pragma once
#include "../Core/LayerSystem.h"
#include "Event.h"

namespace Engine3D
{
    class EventSystem
    {
    public:
        static void Initialize(GLFWwindow* WINDOW, LayerSystem* layerSystem)
        {
            EventSystem::m_WINDOW = WINDOW;
            EventSystem::m_LayerSystem = layerSystem;
            glfwSetKeyCallback(WINDOW, m_KeyCallCallback);
            glfwSetCursorPosCallback(WINDOW, m_MouseCursorCallback);
            glfwSetMouseButtonCallback(WINDOW, m_MouseButtonCallback);
        }

    private:
        // Callbacks
        static GLFWwindow* m_WINDOW;
        static LayerSystem* m_LayerSystem;
        static void m_KeyCallCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            if (action == GLFW_REPEAT)
				return;
            bool isDown = action == GLFW_PRESS;
            auto event = new KeyboardEvent(key, isDown);
            m_LayerSystem->OnEvent(event, EventType::KeyboardEvent);

        }
        static void m_MouseCursorCallback(GLFWwindow* window, double xPos, double yPos)
        {
            auto event = new MouseMovedEvent(xPos, yPos);
			m_LayerSystem->OnEvent(event, EventType::MouseMovedEvent);
        }
        static void m_MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
        {
            bool isDown = action == GLFW_PRESS;
			auto event = new MouseButtonEvent(button, isDown);
        }
	};
}

