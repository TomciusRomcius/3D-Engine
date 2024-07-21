#include "enpch.h"
#include "Hierarchy.h"
#include "ObjectSystem.h"
#include "SceneInformation.h"
#include "Components/Transform.h"
#include "Components/Mesh.h"
#include "Components/MeshRenderer.h"

namespace Engine3D
{
	Hierarchy::Hierarchy()
	{

	}
	void Hierarchy::Start()
	{
	}


	void Hierarchy::Update()
	{
		ImGui::Begin("Scene Hierarchy");
		m_IsHovered = ImGui::IsWindowHovered();
		auto& objects = sceneManager.CurrentScene().namedObjects;
		RenderPopUp();
		for (auto& object : objects)
		{
			if (ImGui::Button(object.first.c_str(), ImVec2(ImGui::GetContentRegionAvail().x, 0)))
			{
				sceneInformation.selectedObject = object.second;
			}
		}

		ImGui::End();
	}

	void Hierarchy::RenderPopUp()
	{
		if (!m_IsPopupOpen) return;
		ImGui::SetNextWindowPos(m_PopupPos);
		ImGui::Begin("Hierarchy dropdown");
		if (ImGui::Button("Create Empty"))
		{
			std::string name = "Empty";
			int i = 0;

			
			Object* object = new Object(name);
			object->AddComponent<Transform>();
			object->AddComponent<Mesh>();
			object->AddComponent<MeshRenderer>();
			object->GetComponent<Transform>().position.z = -15;
			object->GetComponent<Transform>().rotation.y = 45;
			object->GetComponent<Mesh>().LoadModel("Cube.obj");
			m_IsPopupOpen = false;
		}
		ImGui::End();
	}

	void Hierarchy::OnEvent(Event* event, EventType eventType)
	{
		if (eventType == EventType::MouseButtonEvent)
		{
			MouseButtonEvent* mouseEvent = (MouseButtonEvent*)event;
			if (mouseEvent->GetButton() == GLFW_MOUSE_BUTTON_RIGHT && mouseEvent->IsDown())
			{
				if (!m_IsHovered)
				{
					sceneInformation.selectedObject = nullptr;
				}
				else
				{
					m_IsPopupOpen = !m_IsPopupOpen;
					m_PopupPos = ImGui::GetMousePos();
				}
			}

		}
	}
}

