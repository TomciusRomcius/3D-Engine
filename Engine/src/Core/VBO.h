#pragma once
#include "Log.h"
#include "BufferElement.h"

namespace Engine3D
{
	class ENGINE_API VBO
	{
	public:
		explicit VBO(const std::vector<BufferElement>& buffers);
		explicit VBO(const std::vector<glm::vec3>& vertices);
		explicit VBO(const std::vector<glm::vec3>& vertices, const std::vector<glm::vec2>& texCoords);
		explicit VBO(const std::vector<glm::vec3>& vertices, const std::vector<glm::vec2>& texCoords, const std::vector<glm::vec3>& normals);

		void Bind() const;
		~VBO();
	private:
		unsigned int id;
		unsigned int VAO;
	};

}
