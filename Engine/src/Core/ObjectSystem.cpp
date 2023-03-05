#include "enpch.h"
#include "ObjectSystem.h"

// Define the static variables

std::mutex ComponentManager::mutex;

OIdHander* OIdHander::instance = nullptr;
std::mutex OIdHander::mutex;
std::queue<unsigned int> OIdHander::mAvailableIds;
ComponentManager* ComponentManager::instance = nullptr;



OIdHander* OIdHander::GetInstance()
{
	std::lock_guard<std::mutex> lock(mutex);
	if (instance == nullptr) {
		instance = new OIdHander();
		std::cout << "New Instance" << std::endl;
		for (int i = 0; i < MAX_OBJECTS; i++)
		{
			mAvailableIds.push(i);
		}
	}
	return instance;
}

std::queue<unsigned int>& OIdHander::GetIds()
{
	return mAvailableIds;
}

inline Object::Object() {
	if (OIdHander::GetInstance()->mAvailableIds.empty()) {
		std::cout << "Forgot to init queue" << std::endl;
	}
	mId = OIdHander::GetInstance()->mAvailableIds.front();;
	OIdHander::GetInstance()->mAvailableIds.pop();
}

inline Object::~Object() {
	OIdHander::GetInstance()->mAvailableIds.push(mId);
}

ComponentManager& ComponentManager::GetInstance()
{

	if (instance == nullptr)
	{
		instance = new ComponentManager();
		std::cout << "Cmanager" << std::endl;

		return *instance;
	}
	return *instance;
}

void ComponentManager::Update() // Gets called every frame
{
	// Call update on all component arrays
	std::lock_guard<std::mutex> lock(mutex);
	for (auto componentA : instance->mComponentArrays)
	{
		componentA.second.get()->Update();
	}
}
