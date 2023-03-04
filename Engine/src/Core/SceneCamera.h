#pragma once
#include "Time.h"
#include "Event.h"

namespace Engine3D
{
	class SceneCamera
	{
	public:
		static void Move();
		static glm::mat4 ViewMatrix();
		static glm::vec3 Position();
		static glm::vec3 Direction();
		static glm::vec3 Up();
	private:
		static bool active;
		static glm::vec3 position;
		static glm::vec3 direction;
		static glm::vec3 front;
		static glm::vec3 up;
		static float yaw;
		static float pitch;
		
		static glm::vec2 lastMousePos;
	};
}
