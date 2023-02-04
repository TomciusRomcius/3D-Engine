#pragma once

namespace Engine3D
{
	class VBO
	{
	public:
		explicit VBO(const std::vector<glm::vec3>& vertices);
		void Bind() const;
	private:
		unsigned int id;
	};
}
