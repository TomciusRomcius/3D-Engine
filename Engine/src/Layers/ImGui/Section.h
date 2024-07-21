#pragma once
#include "Events/EventSystem.h"
#include "imgui.h"

namespace Engine3D
{
	class Section
	{
	public:
		virtual void Start() = 0;
		virtual void Update() = 0;
		virtual void OnEvent(Event* event, EventType type) = 0;
		virtual ~Section() {};
	};
}