#pragma once
#include "Core/Layer.h"
namespace Engine3D
{
	class ImGuiLayer : public Layer
	{
		public:
		ImGuiLayer(std::string name)
			: Layer(name)
		{ }
		~ImGuiLayer()
		{ }
		void OnAttach() override
		{
			std::cout << "ImGuiLayer attached" << std::endl;
		}
		void OnDetach()
		{
			std::cout << "ImGuiLayer detached" << std::endl;
		}
		void Update() override
		{
		}
		void OnEvent(Event* event, EventType eventType)
		{
			if (eventType == EventType::KeyboardEvent)
			{
				// Dynamic cast
				auto keyboardEvent = dynamic_cast<KeyboardEvent*>(event);
				std::cout << "Key pressed: " << keyboardEvent->GetKeyCode() << std::endl;
			}
		}

	};
}