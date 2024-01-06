#pragma once
#include "Events/Event.h"

namespace Engine3D
{
	class Layer
	{
		friend class LayerSystem;
	public:
		Layer(std::string name);
		~Layer();
		inline std::string GetName() const { return m_Name; }
		virtual void OnAttach() = 0;
		virtual void OnDetach() = 0;
		virtual void Update() = 0;
		virtual void OnEvent(Event* event, EventType eventType) = 0;
	protected:
		std::string m_Name;
		GLFWwindow* m_WINDOW;
		std::vector<Layer*>* m_OtherLayers;
	};
}

