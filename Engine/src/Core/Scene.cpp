#include "enpch.h"
#include "Scene.h"

namespace Engine3D
{
	Scene::Scene() {
		objects = std::unordered_map<std::string, Object*>();
	}
	Scene::~Scene()
	{
		for (auto& object : objects)
		{
			delete object.second;
		}
	
	}
	Object* Scene::FindObjectById(const std::string& id)
	{
		return objects[id];
	}

	Object* Scene::FindObjectByName(const std::string& name)
	{
		return namedObjects[name];
	}

	void Scene::Update()
	{
		SceneCamera::Move();
	}
}