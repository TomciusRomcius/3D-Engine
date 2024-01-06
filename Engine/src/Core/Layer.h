#pragma once
#include "Events/Event.h"

namespace Engine3D
{
	class Layer
	{
	public:
		Layer(std::string name)
			: m_Name(name)
		{ }
		~Layer()
		{ }
		virtual void OnAttach() = 0;
		virtual void OnDetach() = 0;
		virtual void Update() = 0;
		virtual void OnEvent(Event* event, EventType eventType) = 0;
	private:
		std::string m_Name;
	};
}

