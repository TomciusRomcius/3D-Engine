#include "../pch.h"
#include "Transform.h"

namespace Engine3D
{
	void Transform::Start()
	{
		position = { 0, 0, -3 };
		scale = { 1, 1, 1 };
		rotation = { 0, 0, 0 };
	}

	void Transform::Update()
	{
		UpdateMatrices();
	}

	void Transform::UpdateMatrices()
	{


		model = glm::mat4(1.0f);
		view = glm::mat4(1.0f);
		projection = glm::mat4(1.0f);

		model = glm::translate(model, position);
		model = glm::scale(model, scale);
		model = glm::rotate(model, glm::radians(rotation.x), { 1, 0, 0 });
		model = glm::rotate(model, glm::radians(rotation.y), { 0, 1, 0 });
		model = glm::rotate(model, glm::radians(rotation.z), { 0, 0, 1 });

		view = SceneCamera::ViewMatrix();

		projection = glm::perspective(glm::radians(45.f), 16.f / 9.f, .1f, 100.f);

		mvp = projection * view * model; // Matrix multiplication is backward
	}

	glm::mat4 Transform::Mvp() const
	{
		return mvp;
	}
}