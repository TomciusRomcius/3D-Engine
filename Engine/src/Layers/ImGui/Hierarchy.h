#pragma once
#include "Section.h"

namespace Engine3D
{
	class Hierarchy : public Section
	{
	public:
		Hierarchy();
		void Start() override;
		void Update() override;
		void OnEvent(Event* event, EventType eventType);
		void RenderPopUp();
	private:
		bool m_IsHovered = false;
		bool m_IsPopupOpen = false;
		ImVec2 m_PopupPos{};
	};
}

