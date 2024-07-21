#pragma once
#include "ObjectSystem.h"

namespace Engine3D
{
	struct SceneInformation
	{
		Object* selectedObject = nullptr;
	};

	extern SceneInformation sceneInformation;
}