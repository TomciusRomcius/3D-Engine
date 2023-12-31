#include "enpch.h"
#include "ObjectSystem.h"
#include <mutex>

namespace Engine3D
{
	OIdHander* OIdHander::instance = nullptr;
	std::mutex OIdHander::mutex;
	std::queue<unsigned int> OIdHander::mAvailableIds;

	OIdHander* OIdHander::GetInstance()
	{
		std::lock_guard<std::mutex> lock(mutex);
		if (instance == nullptr) {
			instance = new OIdHander();
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

	Object::Object()
		: mId(OIdHander::GetInstance()->mAvailableIds.front())
	{
		if (OIdHander::GetInstance()->mAvailableIds.empty()) {
			EN_CORE_ERROR("Forgot to initialize queue or reached max objects");
			return;
		}

		SceneManager::CurrentScene().objects[std::to_string(OIdHander::GetInstance()->mAvailableIds.front())] = this;
		OIdHander::GetInstance()->mAvailableIds.pop();
	}

	Object::Object(std::string name)
		: mId(OIdHander::GetInstance()->mAvailableIds.front())
	{
		if (OIdHander::GetInstance()->mAvailableIds.empty()) {
			EN_CORE_ERROR("Forgot to initialize queue or reached max objects");
			return;
		}

		SceneManager::CurrentScene().objects[std::to_string(OIdHander::GetInstance()->mAvailableIds.front())] = this;
		SceneManager::CurrentScene().namedObjects[name] = this;
		OIdHander::GetInstance()->mAvailableIds.pop();
	}

	Object::Object(std::string name, std::vector<std::string> tags)
		: mId(OIdHander::GetInstance()->mAvailableIds.front())
	{
		if (OIdHander::GetInstance()->mAvailableIds.empty()) {
			EN_CORE_ERROR("Forgot to initialize queue or reached max objects");
			return;
		}

		if (SceneManager::CurrentScene().namedObjects.find(name) != SceneManager::CurrentScene().namedObjects.end()) {
			EN_CORE_ERROR("Object with name {0} already exists", name);
			return;
		}
		SceneManager::CurrentScene().namedObjects[name] = this;
		SceneManager::CurrentScene().objects[std::to_string(OIdHander::GetInstance()->mAvailableIds.front())] = this;
		SceneManager::CurrentScene().taggedObjects[tags[0]].push_back(this);
		OIdHander::GetInstance()->mAvailableIds.pop();
	}

	Object::Object(std::vector<std::string> tags)
		: mId(OIdHander::GetInstance()->mAvailableIds.front())
	{
		if (OIdHander::GetInstance()->mAvailableIds.empty()) {
			EN_CORE_ERROR("Forgot to initialize queue or reached max objects");
			return;
		}

		SceneManager::CurrentScene().objects[std::to_string(OIdHander::GetInstance()->mAvailableIds.front())] = this;
		SceneManager::CurrentScene().taggedObjects[tags[0]].push_back(this);
		OIdHander::GetInstance()->mAvailableIds.pop();
	}

	inline Object::~Object() {
		SceneManager::CurrentScene().objects.erase(std::to_string(mId));
		OIdHander::GetInstance()->mAvailableIds.push(mId);
	}
}
