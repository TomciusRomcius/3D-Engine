#pragma once
#include "BufferElement.h"
#include "Log.h"

namespace Engine3D
{
	class VertexArray
	{
	public:
		VertexArray(std::vector<BufferElement> buffers);
		~VertexArray() {};

		inline void Bind() { glBindVertexArray(m_Id); };
		inline void UnBind() { glBindVertexArray(0); };
		inline unsigned int Id() { return m_Id; };
	private:
		unsigned int m_Id;
	};
}

