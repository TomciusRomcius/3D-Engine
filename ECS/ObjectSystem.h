#pragma once
#include "ComponentManager.h"
#include "SceneManager.h"

extern SceneManager sceneManager;
extern OIdHander oIdHander;
extern const unsigned int MAX_OBJECTS;
extern ComponentManager componentManager;
class DLL_EXPORT Object {
public:
	Object();
	Object(std::string name);
	Object(std::string name, std::vector<std::string> tags);
	Object(std::vector<std::string> tags);
	template <typename T>
	void AddComponent() {
		componentManager.AddComponent<T>(this->mId, this);
	}

	template <typename T>
	T& GetComponent() {
		return componentManager.GetComponent<T>(this->mId);
	}

	template <typename T>
	void RemoveComponent() {
		componentManager.RemoveComponent<T>(this->mId);
	}

	~Object();
	unsigned int Id() { return mId; }
private:
	ObjectID mId;
	std::string name;
	std::vector<std::string> tags;
	std::bitset<MAX_COMPONENTS> mComponentBitset;
};