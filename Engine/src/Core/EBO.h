#pragma once
#include "Log.h"

namespace Engine3D
{
	class ENGINE_API EBO
	{
	public:
		explicit EBO(const std::vector<unsigned int>& indices);
		void Bind() const;
		~EBO();
	private:
		unsigned int id;
	};
}



