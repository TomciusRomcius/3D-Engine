#include "enpch.h"
#include "EventSystem.h"
#include "Event.h"

namespace Engine3D
{
	GLFWwindow* EventSystem::m_WINDOW = nullptr;
	LayerSystem* EventSystem::m_LayerSystem = nullptr;

    void EventSystem::Initialize(GLFWwindow* WINDOW, LayerSystem* layerSystem)
    {
        EventSystem::m_WINDOW = WINDOW;
        EventSystem::m_LayerSystem = layerSystem;
        glfwSetKeyCallback(WINDOW, m_KeyCallCallback);
        glfwSetCursorPosCallback(WINDOW, m_MouseCursorCallback);
        glfwSetMouseButtonCallback(WINDOW, m_MouseButtonCallback);
    }
    void EventSystem::m_KeyCallCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if (action == GLFW_REPEAT)
            return;
        bool isDown = action == GLFW_PRESS;
        auto event = new KeyboardEvent(key, isDown);
        m_LayerSystem->OnEvent(event, EventType::KeyboardEvent);

    }
    void EventSystem::m_MouseCursorCallback(GLFWwindow* window, double xPos, double yPos)
    {
        auto event = new MouseMovedEvent(xPos, yPos);
        m_LayerSystem->OnEvent(event, EventType::MouseMovedEvent);
    }
    void EventSystem::m_MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
    {
        bool isDown = action == GLFW_PRESS;
        auto event = new MouseButtonEvent(button, isDown);
        m_LayerSystem->OnEvent(event, EventType::MouseButtonEvent);
    }
}
