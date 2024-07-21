#include "enpch.h"
#include "BufferElement.h"

namespace Engine3D
{
	BufferElement::BufferElement(void* data,
				BufferDataType type,
				unsigned int sizeCount,
				unsigned int count
				, bool normalized)
		: m_Data(data), m_Type(type), m_SizeCount(sizeCount), m_Count(count), m_Stride(), m_Normalized(normalized)
	{
		int typeSize;
		switch (type)
		{
		case BufferDataType::Float:
			typeSize = sizeof(float);
			break;
		case BufferDataType::Double:
			typeSize = sizeof(double);
			break;
		case BufferDataType::Int:
			typeSize = sizeof(int);
			break;
		case BufferDataType::UInt:
			typeSize = sizeof(unsigned int);
			break;
		default:
			typeSize = 0;
			EN_CORE_ERROR("Unknown BufferDataType");
		}
		m_Size = m_SizeCount * typeSize * m_Count;
		m_Stride = m_Count * typeSize;
	}
}