#include "../pch.h"
#include "VBO.h"

namespace Engine3D
{
	VBO::VBO(const std::vector<glm::vec3>& vertices)
	{
		unsigned int VAO;
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		glGenBuffers(1, &id);
		glBindBuffer(GL_ARRAY_BUFFER, id);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * 3 * sizeof(float), vertices.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
		glEnableVertexAttribArray(0);

	}


	void VBO::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, id);
	}
}
