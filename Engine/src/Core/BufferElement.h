#pragma once
#include "Log.h"

namespace Engine3D
{
	enum BufferDataType
	{
		Float,
		Double,
		Int,
		UInt
	};
	class BufferElement
	{
	public:
		BufferElement(void* data,
					BufferDataType type,
					unsigned int sizeCount,
					unsigned int count,
					bool normalized = false);
		inline void* GetData() const { return m_Data; }
		inline BufferDataType GetType() const { return m_Type; }
		inline unsigned int GetSize() const { return m_Size; }
		inline unsigned int GetSizeCount() const { return m_SizeCount; }
		inline unsigned int GetCount() const { return m_Count; }
		inline unsigned int GetStride() const { return m_Stride; }
		inline bool IsNormalized() const { return m_Normalized; }
	private:
		void* m_Data;
		BufferDataType m_Type;
		unsigned int m_Size;
		unsigned int m_SizeCount;
		unsigned int m_Count;
		unsigned int m_Stride;
		bool m_Normalized;
	};
}

