#pragma once
#include "ComponentManager.h"


// OIdHander.h - header file
class ENGINE_API OIdHander {
private:	
	static std::mutex mutex;
	static OIdHander* instance;
	// Private constructor to prevent instantiation
	OIdHander() {}

public:
	// Public method to get the OIdHander instance
	static OIdHander* GetInstance();
	static std::queue<unsigned int> mAvailableIds;

	std::queue<unsigned int>& GetIds();
};


class ENGINE_API Object {
public:
	Object();
	template <typename T>
	void AddComponent() {
		ComponentManager::GetInstance().AddComponent<T>(this->mId, this);
	}

	template <typename T>
	T& GetComponent() {
		return ComponentManager::GetInstance().GetComponent<T>(this->mId);
	}

	template <typename T>
	void RemoveComponent() {
		ComponentManager::GetInstance().RemoveComponent<T>(this->mId);
	}

	~Object();
	unsigned int Id() { return mId; }
private:
	ObjectID mId;
	std::bitset<MAX_COMPONENTS> mComponentBitset;
};

