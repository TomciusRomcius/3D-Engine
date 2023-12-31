#pragma once
#include "Window/OpenGLWindow.h"

namespace Engine3D
{
	enum class RenderAPI
	{
		None = 0,
		OpenGL = 1,
		DirectX = 2
	};

	class Application
	{
	public:
		void Initialize(RenderAPI api)
		{
			switch (api)
			{
			case RenderAPI::None:
				return;
			case RenderAPI::OpenGL:
				window = std::make_unique<OpenGLWindow>();
				break;
			case RenderAPI::DirectX:
				return;
			}
		}

		void Run() {	
			window->Initialize(std::bind(
				&Application::Start, this),
				std::bind(&Application::Update, this)
			);
		};

		virtual void Start() = 0;
		virtual void Update() = 0;

	private:
		std::unique_ptr<IWindow> window;
	};
}
