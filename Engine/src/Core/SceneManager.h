#pragma once
#include "Scene.h"
#include "Log.h"
#include "SceneCamera.h"

	
namespace Engine3D
{
	class ENGINE_API SceneManager
	{
	public:
		static void Initialize();
		static Scene& CreateScene(const std::string& id);
		static inline Scene& CurrentScene();
	private:
		static Scene* currentScene;
		static std::unordered_map<std::string, Scene> scenes; // Id to scene
	};
}

