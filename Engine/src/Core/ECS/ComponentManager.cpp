#include "enpch.h"
#include "ComponentManager.h"

std::mutex ComponentManager::mutex;
ComponentManager* ComponentManager::instance = nullptr;

inline ComponentManager& ComponentManager::GetInstance()
{

	if (instance == nullptr)
	{
		instance = new ComponentManager();

		return *instance;
	}
	return *instance;
}

inline void ComponentManager::Update() // Gets called every frame
{
	// Call update on all component arrays
	std::lock_guard<std::mutex> lock(mutex);
	for (auto componentA : instance->mComponentArrays)
	{
		componentA.second.get()->Update();
	}
}
