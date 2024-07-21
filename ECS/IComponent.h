#pragma once
#include "ObjectSystem.h"

namespace EngineECS
{
	struct DLL_EXPORT IComponent
	{
		virtual void Start() = 0;
		virtual void Update() = 0;
		Object* object;
	};
}

