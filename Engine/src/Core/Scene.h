#pragma once
#include "SceneCamera.h"

namespace Engine3D
{
	class Object; // Forward declare from ECS/Object.h
	const long id = 0;

	class ENGINE_API Scene
	{
	public:
		Scene();
		~Scene();
		Object* FindObjectById(const std::string& id);
		Object* FindObjectByName(const std::string& name);
		void Update();
		std::unordered_map<std::string, Object*> objects;
		std::unordered_map<std::string, Object*> namedObjects;
		std::unordered_map<std::string, std::vector<Object*>> taggedObjects;
	private:
	};
}
