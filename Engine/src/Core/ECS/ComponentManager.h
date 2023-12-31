#pragma once
#include "ComponentArray.h"


class ENGINE_API ComponentManager // Holds all component arrays
{
public:
	static ComponentManager& GetInstance();
	static void Update(); // Gets called every frame

	template <typename T>
	void RegisterComponent();
	template <typename T>
	void AddComponent(ObjectID id, Object* object);
	template <typename T>
	void RemoveComponent(ObjectID id);
	template <typename T>
	T& GetComponent(ObjectID id);
	std::unordered_map<std::string, std::shared_ptr<IComponentArray>> mComponentArrays;

private:
	static std::mutex mutex;
	static ComponentManager* instance;

	template <typename T>
	std::shared_ptr<ComponentArray<T>> GetComponentArray();
};

template<typename T>
inline void ComponentManager::RegisterComponent() // Call this before adding a component for the first tie
{
	const char* typeName = typeid(T).name();
	mComponentArrays.insert({ typeName, std::make_shared<ComponentArray<T>>() });
}

template<typename T>
inline void ComponentManager::AddComponent(ObjectID id, Object* object) // Adds a component to a given object
{
	if (mComponentArrays.find(typeid(T).name()) == mComponentArrays.end())
	{
		RegisterComponent<T>();
	}
	GetComponentArray<T>()->InsertData(id, object);
}

template<typename T>
inline void ComponentManager::RemoveComponent(ObjectID id) // Removes component from a given object
{
	GetComponentArray<T>()->RemoveData(id);
}

template<typename T>
inline T& ComponentManager::GetComponent(ObjectID id) // Returns the component of the given object
{
	return GetComponentArray<T>()->GetData(id);
}

template<typename T>
inline std::shared_ptr<ComponentArray<T>> ComponentManager::GetComponentArray() // Gets the component array based of the name
{
	std::string typeName = typeid(T).name();
	return std::static_pointer_cast<ComponentArray<T>>(mComponentArrays.at(typeName));
}
