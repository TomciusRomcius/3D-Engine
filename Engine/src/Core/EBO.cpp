#include "enpch.h"
#include "EBO.h"

namespace Engine3D
{
	EBO::EBO(const std::vector<unsigned int>& indices)
	{
		glGenBuffers(1, &id);
		EN_TRACE("Creating element buffer object id = " + std::to_string(id));

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);

	}

	void EBO::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	}
	EBO::~EBO()
	{
		EN_TRACE("Deleting element buffer object id = " + std::to_string(id));
		glDeleteBuffers(1, &id);
	}
}
