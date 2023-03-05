#include "enpch.h"
#include "VBO.h"

namespace Engine3D
{
	VBO::VBO(const std::vector<glm::vec3>& vertices, const std::vector<glm::vec2> texCoords)
	{
		unsigned int VAO;
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		glGenBuffers(1, &id);

		EN_TRACE("Creating vertex buffer object id = " + std::to_string(id));

		glBindBuffer(GL_ARRAY_BUFFER, id);

		unsigned int verticesSize = vertices.size() * 3 * sizeof(float);
		unsigned int texCoordsSize = texCoords.size() * 2 * sizeof(float);

		glBufferData(GL_ARRAY_BUFFER, verticesSize + texCoordsSize, vertices.data(), GL_STATIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, verticesSize, vertices.data());
		glBufferSubData(GL_ARRAY_BUFFER, verticesSize, texCoordsSize, vertices.data());

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)verticesSize);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

	}
	VBO::VBO(const std::vector<glm::vec3>& vertices)
	{
		unsigned int VAO;
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		glGenBuffers(1, &id);

		EN_TRACE("Creating vertex buffer object id = " + std::to_string(id));

		glBindBuffer(GL_ARRAY_BUFFER, id);

		glBufferData(GL_ARRAY_BUFFER, vertices.size() * 3 * sizeof(float), vertices.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
		glEnableVertexAttribArray(0);

	}

	void VBO::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, id);
	}
	VBO::~VBO()
	{
		EN_TRACE("Deleting vertex buffer object id = " + std::to_string(id));

		glDeleteBuffers(1, &id);
	}
}
