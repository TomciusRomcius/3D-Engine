#include "enpch.h"
#include "SceneManager.h"

namespace Engine3D
{
	void SceneManager::Initialize()
	{
		currentScene = &CreateScene("Default");
	}

	Scene& SceneManager::CreateScene(const std::string& id)
	{
		if (scenes.find(id) != scenes.end()) {
			EN_CORE_ERROR("Scene with id {0} already exists", id);
			return scenes[id];
		}
		scenes[id] = Scene();
		return scenes[id];
	}

	inline Scene& SceneManager::CurrentScene()
	{
		return *currentScene;
	}
	Scene* SceneManager::currentScene = nullptr;
	std::unordered_map<std::string, Scene> SceneManager::scenes{};
}
