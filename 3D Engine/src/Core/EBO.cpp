#include "../pch.h"
#include "EBO.h"

namespace Engine3D
{
	EBO::EBO(const std::vector<unsigned int>& indices)
	{
		glGenBuffers(1, &id);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

	}

	void EBO::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	}
}
