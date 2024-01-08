#pragma once
#include "Section.h"

namespace Engine3D
{
	class Inspector : public Section
	{
	public:
		Inspector();
		void Start() override;
		void Update() override;
		void OnEvent(Event* event, EventType type) override;
	};
}

