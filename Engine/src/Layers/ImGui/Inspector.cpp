#include "enpch.h"
#include "Inspector.h"
#include "SceneInformation.h"
#include "Components/Transform.h"
#include "Components/MeshRenderer.h"
#include "Components/Mesh.h"

namespace Engine3D
{
	Inspector::Inspector() { }

	void Inspector::Start()
	{

	}

	void Inspector::Update()
	{
		ImGui::Begin("Inspector");
		if (sceneInformation.selectedObject != nullptr)
		{
			ImGui::Text(std::to_string(sceneInformation.selectedObject->Id()).c_str());
			auto& transform = sceneInformation.selectedObject->GetComponent<Transform>();
			auto& meshRenderer = sceneInformation.selectedObject->GetComponent<MeshRenderer>();
			auto& mesh = sceneInformation.selectedObject->GetComponent<Mesh>();
			if (ImGui::TreeNode("Transform"))
			{
				ImGui::DragFloat3("Position", &transform.position.x, 0.1f);
				ImGui::DragFloat3("Rotation", &transform.rotation.x, 0.1f);
				ImGui::DragFloat3("Scale", &transform.scale.x, 0.1f);
				ImGui::TreePop();
			}
			if (ImGui::TreeNode("Mesh"))
			{
				std::string loadedModel = mesh.GetLoadedModel();
				if (loadedModel != "")
				{
					ImGui::Text(("Loaded model: " + loadedModel).c_str());
				}
				else
				{
					ImGui::Text("No model loaded");
				}
				ImGui::Button("Load model");
				ImGui::TreePop();
			}

			static bool open = true;

			if (ImGui::Button("Load component")) open = !open;
			if (open)
			{
				const int MAX_NAME_LENGTH = 50;
				static char name[MAX_NAME_LENGTH] = "";
				ImGui::InputText("Component name", name, MAX_NAME_LENGTH);
				ImGui::Text("Entered text: %s", name);
				if (ImGui::Button("Load"))
				{
				}
			}
		}
		ImGui::End();
	}

	void Inspector::OnEvent(Event* event, EventType eventType)
	{

	}
}