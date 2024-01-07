#include "pch.h"
#include "SceneManager.h"

extern OIdHander oIdHander;
SceneManager sceneManager = SceneManager();
SceneManager::SceneManager()
{
	currentScene = &CreateScene("Default");
}

Scene& SceneManager::CreateScene(const std::string& id)
{
	if (scenes.find(id) != scenes.end()) {
		std::cout << "Scene with id " << id << " already exists" << std::endl;
		return scenes[id];
	}
	scenes[id] = Scene();
	return scenes[id];
}

Scene& SceneManager::CurrentScene()
{
	return *currentScene;
}

