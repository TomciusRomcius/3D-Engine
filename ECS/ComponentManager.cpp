#include "pch.h"
#include "ComponentManager.h"

ComponentManager::ComponentManager() { }

void ComponentManager::Update() // Gets called every frame
{
	// Call update on all component arrays
	std::lock_guard<std::mutex> lock(mutex);
	for (auto componentA : mComponentArrays)
	{
		componentA.second.get()->Update();
	}
}
