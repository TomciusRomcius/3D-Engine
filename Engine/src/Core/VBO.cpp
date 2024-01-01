#include "enpch.h"
#include "VBO.h"

namespace Engine3D
{
	VBO::VBO(const std::vector<glm::vec3>& vertices, const std::vector<glm::vec2>& texCoords, const std::vector<glm::vec3>& normals)
	{
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		glGenBuffers(1, &id);

		EN_TRACE("Creating vertex buffer object id = " + std::to_string(id));

		glBindBuffer(GL_ARRAY_BUFFER, id);

		unsigned int verticesSize = vertices.size() * 3 * sizeof(float);
		unsigned int texCoordsSize = texCoords.size() * 2 * sizeof(float);
		unsigned int normalsSize = normals.size() * 3 * sizeof(float);

		glBufferData(GL_ARRAY_BUFFER, verticesSize + texCoordsSize + normalsSize, 0, GL_STATIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, verticesSize, vertices.data());
		glBufferSubData(GL_ARRAY_BUFFER, verticesSize, texCoordsSize, texCoords.data());
		glBufferSubData(GL_ARRAY_BUFFER, verticesSize + texCoordsSize, normalsSize, normals.data());

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)verticesSize);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(verticesSize + texCoordsSize));
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
	}

	VBO::VBO(const std::vector<glm::vec3>& vertices, const std::vector<glm::vec2>& texCoords)
	{
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		glGenBuffers(1, &id);

		EN_TRACE("Creating vertex buffer object id = " + std::to_string(id));

		glBindBuffer(GL_ARRAY_BUFFER, id);

		unsigned int verticesSize = vertices.size() * 3 * sizeof(float);
		unsigned int texCoordsSize = texCoords.size() * 2 * sizeof(float);

		glBufferData(GL_ARRAY_BUFFER, verticesSize + texCoordsSize, 0, GL_STATIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, verticesSize, vertices.data());
		glBufferSubData(GL_ARRAY_BUFFER, verticesSize, texCoordsSize, texCoords.data());

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)verticesSize);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
	}

	VBO::VBO(const std::vector<BufferElement>& buffers)
	{
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		glGenBuffers(1, &id);

		EN_TRACE("Creating vertex buffer object id = " + std::to_string(id));
		unsigned int size = 0;
		for (auto& buffer : buffers)
		{
			size += buffer.GetSize();
		};

		glBindBuffer(GL_ARRAY_BUFFER, id);
		glBufferData(GL_ARRAY_BUFFER, size, 0, GL_STATIC_DRAW);

		auto offset = 0;
		for (int i = 0; i < buffers.size(); i++)
		{
			glBufferSubData(GL_ARRAY_BUFFER, offset, buffers[i].GetSize(), buffers[i].GetData());
			offset += buffers[i].GetSize();
		}
		offset = 0;
		for (int i = 0; i < buffers.size(); i++)
		{
			auto bufferType = buffers[i].GetType();
			int openGLType = GL_FLOAT;
			switch (bufferType)
			{
				case BufferDataType::Float:
					openGLType = GL_FLOAT;
					break;
				case BufferDataType::Double:
					openGLType = GL_DOUBLE;
					break;
				case BufferDataType::Int:
					openGLType = GL_INT;
					break;
				case BufferDataType::UInt:
					openGLType = GL_UNSIGNED_INT;
					break;
			}
			glVertexAttribPointer(i,
								buffers[i].GetCount(),
								openGLType,
								GL_FALSE,
								buffers[i].GetStride(),
								(void*)offset);
			glEnableVertexAttribArray(i);
			offset += buffers[i].GetSize();
		}
	}

	VBO::VBO(const std::vector<glm::vec3>& vertices)
	{
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
		glBindVertexArray(VAO);
	}
	VBO::~VBO()
	{
		EN_TRACE("Deleting vertex buffer object id = " + std::to_string(id));

		glDeleteBuffers(1, &id);
	}
}
