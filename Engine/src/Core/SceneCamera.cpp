#include "enpch.h"
#include "SceneCamera.h"

namespace Engine3D
{
	void SceneCamera::Move()
	{
		//if (!Event::GetMouseButtonDown(GLFW_MOUSE_BUTTON_RIGHT))
		//{
			//Event::CursorMode(GLFW_CURSOR_NORMAL);
			return;
		//}
		//Event::CursorMode(GLFW_CURSOR_DISABLED);


		const float cameraSpeed = 20.f; // adjust accordingly
		const float sensitivity = 100.f; // adjust accordingly

		//float dx = Event::mousePos.x - lastMousePos.x;
		//float dy = Event::mousePos.y - lastMousePos.y;

		//yaw += dx * sensitivity * Time::DeltaTime;
		//pitch += dy * sensitivity * Time::DeltaTime;

		if (pitch > 90.f) pitch = 90.f; // Clamping
		if (pitch < -90.f) pitch = -89.f;

		// Getting the direction in which the camera is facing
		direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		direction.y = sin(glm::radians(pitch));
		direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		direction = glm::normalize(direction);

		//lastMousePos = Event::mousePos;

		// Moving the camera
		//if (Event::GetKey(GLFW_KEY_W))
		//	position += cameraSpeed * direction * Time::DeltaTime;
		//if (Event::GetKey(GLFW_KEY_S))
		//	position -= cameraSpeed * direction * Time::DeltaTime;
		//if (Event::GetKey(GLFW_KEY_A))
		//	position -= glm::normalize(glm::cross(direction, up)) * cameraSpeed * Time::DeltaTime;
		//if (Event::GetKey(GLFW_KEY_D))
			position += glm::normalize(glm::cross(direction, up)) * cameraSpeed * Time::DeltaTime;
	}
	glm::mat4 SceneCamera::ViewMatrix()
	{
		return glm::lookAt(position, position + direction, up);
	}
	glm::vec3 SceneCamera::Position()
	{
		return position;
	}
	glm::vec3 SceneCamera::Direction()
	{
		return direction;
	}
	glm::vec3 SceneCamera::Up()
	{
		return up;
	}
	float SceneCamera::yaw{ 0 };
	float SceneCamera::pitch{ 0 };
	glm::vec3 SceneCamera::position{ 0, 0, -3 };
	glm::vec2 SceneCamera::lastMousePos{ 640, 360 };
	glm::vec3 SceneCamera::front{ 0, 0, -1 };
	glm::vec3 SceneCamera::direction{ 0, 0, -1 };
	glm::vec3 SceneCamera::up{ 0, 1, 0 };
}
