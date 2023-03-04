#pragma once


namespace Engine3D
{
    class _declspec(dllexport) Event
    {
    private:
        // Callbacks
        static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void mouseCursorCallback(GLFWwindow* window, double xPos, double yPos);
        static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

    public:
        // This is where we set the GLFW key callback 
        static GLFWwindow* WINDOW;
        static void Initialize(GLFWwindow* WINDOW);
        
        static bool GetKey(int key);
        static bool GetMouseButtonDown(int button);
        static void CursorMode(int mode);

        // Onclick choose what functions get called
        static void BindFunctionKey(int key, std::function<void()> function);
        static void BindFunctionButton(int key, std::function<void()> function);
        static std::multimap<int, std::function<void()>> keyBindings;
        static std::multimap<int, std::function<void()>> buttonBindings;
        static glm::vec2 mousePos;
    };
}
