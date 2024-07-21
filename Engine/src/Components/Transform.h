#pragma once
#include "IComponent.h"
#include "../Core/SceneCamera.h"

namespace Engine3D
{
	class ENGINE_API Transform : public IComponent
	{
	public:
		void Start() override;
		void Update() override;
		glm::mat4 Mvp() const;
		glm::vec3 position;
		glm::vec3 scale;
		glm::vec3 rotation;

	private:
		void UpdateMatrices(); // Responsible for updating matrices
		// Based of position, scale, rotation, distance from camera etc.
		glm::mat4 mvp; // Final matrix
		glm::mat4 model; // Object space
		glm::mat4 view; // World space
		glm::mat4 projection; // Screen space

	};
}