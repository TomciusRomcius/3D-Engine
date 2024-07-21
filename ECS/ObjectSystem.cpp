#include "pch.h"
#include "ObjectSystem.h"
#include <mutex>
#include "OIdHander.h"

ComponentManager componentManager = ComponentManager();
const unsigned int MAX_OBJECTS = 1000;
Object::Object()
	: mId(oIdHander.mAvailableIds.front())
{
	if (oIdHander.mAvailableIds.empty()) {
		std::cout << "Forgot to initialize queue or reached max objects" << std::endl;
		return;
	}

	sceneManager.CurrentScene().objects[std::to_string(oIdHander.mAvailableIds.front())] = this;
	oIdHander.mAvailableIds.pop();
}

Object::Object(std::string name)
	: mId(oIdHander.mAvailableIds.front())
{
	if (oIdHander.mAvailableIds.empty()) {
		std::cout << "Forgot to initialize queue or reached max objects" << std::endl;
		return;
	}

	sceneManager.CurrentScene().objects[std::to_string(oIdHander.mAvailableIds.front())] = this;
	sceneManager.CurrentScene().namedObjects[name] = this;
	oIdHander.mAvailableIds.pop();
}

Object::Object(std::string name, std::vector<std::string> tags)
	: mId(oIdHander.mAvailableIds.front())
{
	if (oIdHander.mAvailableIds.empty()) {
		std::cout << "Forgot to initialize queue or reached max objects" << std::endl;
		return;
	}

	if (sceneManager.CurrentScene().namedObjects.find(name) != sceneManager.CurrentScene().namedObjects.end()) {
		std::cout << "Object with name {0} already exists " << name;
		return;
	}
	sceneManager.CurrentScene().namedObjects[name] = this;
	sceneManager.CurrentScene().objects[std::to_string(oIdHander.mAvailableIds.front())] = this;
	sceneManager.CurrentScene().taggedObjects[tags[0]].push_back(this);
	oIdHander.mAvailableIds.pop();
}

Object::Object(std::vector<std::string> tags)
	: mId(oIdHander.mAvailableIds.front())
{
	if (oIdHander.mAvailableIds.empty()) {
		std::cout << "Forgot to initialize queue or reached max objects" << std::endl;
		return;
	}

	sceneManager.CurrentScene().objects[std::to_string(oIdHander.mAvailableIds.front())] = this;
	sceneManager.CurrentScene().taggedObjects[tags[0]].push_back(this);
	oIdHander.mAvailableIds.pop();
}

inline Object::~Object() {
	sceneManager.CurrentScene().objects.erase(std::to_string(mId));
	oIdHander.mAvailableIds.push(mId);
}
