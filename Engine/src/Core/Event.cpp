#include "enpch.h"
#include "Event.h"

namespace Engine3D
{
    std::multimap<int, std::function<void()>> Event::keyBindings;
    std::multimap<int, std::function<void()>> Event::buttonBindings;
    GLFWwindow* Event::WINDOW;
    glm::vec2 Event::mousePos{ 0, 0 };

    void Event::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if (action == GLFW_PRESS)
        {
            // Find the key pair in the map and iterate through it's functions
            if (keyBindings.count(key) == 0) return;
            auto range = keyBindings.equal_range(key);
            for (auto it = range.first; it != range.second; ++it)
            {
                // Call the function
                it->second();
            }
        }
    }

    void Event::mouseCursorCallback(GLFWwindow* window, double xPos, double yPos)
    {
        mousePos.x = xPos;
        mousePos.y = yPos;
    }

    void Event::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
    {
    }

    void Event::Initialize(GLFWwindow* WINDOW)
    {
        Event::WINDOW = WINDOW;
        glfwSetKeyCallback(WINDOW, keyCallback);
        glfwSetCursorPosCallback(WINDOW, mouseCursorCallback);
        glfwSetMouseButtonCallback(WINDOW, mouseButtonCallback);
    }

    bool Event::GetKey(int key)
    {
        return glfwGetKey(WINDOW, key);
    }

    bool Event::GetMouseButtonDown(int button)
    {
        return glfwGetMouseButton(WINDOW, button);
    }

    void Event::CursorMode(int mode)
    {
        glfwSetInputMode(WINDOW, GLFW_CURSOR, mode);
    }

    void Event::BindFunctionKey(int key, std::function<void()> function)
    {
        keyBindings.insert(std::pair<int, std::function<void()>>(key, function));
    }

    void Event::BindFunctionButton(int key, std::function<void()> function)
    {
    }

}
