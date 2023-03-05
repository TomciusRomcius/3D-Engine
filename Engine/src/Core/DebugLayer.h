#pragma once
#include "Log.h"

namespace Engine3D
{
    class DebugLayer
    {
    public:
        static void Initialize(GLFWwindow* WINDOW);
    private:
        enum class GLError
        {
            NONE = GL_NO_ERROR,
            INVALID_ENUM = GL_INVALID_ENUM,
            INVALID_VALUE = GL_INVALID_VALUE,
            INVALID_OPERATION = GL_INVALID_OPERATION,
            INVALID_FRAMEBUFFER_OPERATION = GL_INVALID_FRAMEBUFFER_OPERATION,
            OUT_OF_MEMORY = GL_OUT_OF_MEMORY
        };

        static void APIENTRY DebugMessageCallback(GLenum source,
            GLenum type,
            GLuint id,
            GLenum severity,
            GLsizei length,
            const GLchar* message,
            const void* userParam);
    };
}
