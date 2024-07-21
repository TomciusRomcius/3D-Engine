#pragma once

#define DLL_EXPORT __declspec(dllexport)
class Object; // Forward declare from ECS/Object.h
const long id = 0;

class DLL_EXPORT Scene
{
public:
	Scene();
	~Scene();
	Object* FindObjectById(const std::string& id);
	Object* FindObjectByName(const std::string& name);
	void Update();
	std::unordered_map<std::string, Object*> objects;
	std::unordered_map<std::string, Object*> namedObjects;
	std::unordered_map<std::string, std::vector<Object*>> taggedObjects;
private:
};