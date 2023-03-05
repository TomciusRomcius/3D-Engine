#pragma once
#include "Log.h"

namespace Engine3D
{
	class ENGINE_API VBO
	{
	public:
		explicit VBO(const std::vector<glm::vec3>& vertices);
		void Bind() const;
		~VBO();
	private:
		unsigned int id;
	};
}
