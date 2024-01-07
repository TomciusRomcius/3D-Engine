#pragma once
#include "../Core/VBO.h"
#include "../Core/EBO.h"
#include "../Core/EBO.h"
#include "ObjectSystem.h"

namespace Engine3D
{
	struct ENGINE_API IComponent
	{
		virtual void Start() = 0;
		virtual void Update() = 0;
		Object* object;
	};
}

