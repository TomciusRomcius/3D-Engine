#pragma once

namespace Engine3D
{
	class EBO
	{
	public:
		explicit EBO(const std::vector<unsigned int>& indices);
		void Bind() const;
	private:
		unsigned int id;
	};
}



