#pragma once

namespace Engine3D
{
	class Shader
	{
	public:
		Shader(unsigned int shaderType, const char* src);
		unsigned int Id() const { return id; };
	private:
		std::string ReadSource(const char* filePath) const;
		unsigned int id;

	};
}
