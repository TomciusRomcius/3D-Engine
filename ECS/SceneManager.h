#pragma once
#include "Scene.h"
#include "OIdHander.h"

extern const unsigned int MAX_OBJECTS;
	
class DLL_EXPORT SceneManager
{
public:
	SceneManager();
	Scene& CreateScene(const std::string& id);
	inline Scene& CurrentScene();
private:
	Scene* currentScene;
	std::unordered_map<std::string, Scene> scenes; // Id to scene
};