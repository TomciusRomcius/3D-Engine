#include "enpch.h"
#include "VertexArray.h"

namespace Engine3D
{
	Engine3D::VertexArray::VertexArray(std::vector<BufferElement> buffers)
		: m_Id(0)
	{
		glGenVertexArrays(1, &m_Id);
		glBindVertexArray(m_Id);
	
		int index = 0;
		int offset = 0;
		for (auto& buffer : buffers)
		{
			int type = buffer.GetType();
			int openGLType = BufferDataType::Float;
			switch (type)
			{
				case BufferDataType::Float:
					openGLType = GL_FLOAT;
					break;
				case BufferDataType::Int:
					openGLType = GL_INT;
					break;
				case BufferDataType::UInt:
					openGLType = GL_UNSIGNED_INT;
					break;
				default:
					EN_CORE_ERROR("Unknown buffer data type");
					break;
			}
			glVertexAttribPointer(index, buffer.GetCount(), openGLType, GL_FALSE, buffer.GetStride(), (void*)offset);
			glEnableVertexAttribArray(index);
			index++;
			offset += buffer.GetSize();
		}
	}
}
