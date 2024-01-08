#include <iostream>
#include "ObjectSystem.h"
#include "IComponent.h"

#define DLL_EXPORT __declspec(dllexport)

class DLL_EXPORT GameComponent : public EngineECS::IComponent
{
public:
	void Start() override
	{

	}
	void Update() override
	{
		std::cout << "Hello from GameComponent" << std::endl;

	}
private:
	Object* m_Object;
};