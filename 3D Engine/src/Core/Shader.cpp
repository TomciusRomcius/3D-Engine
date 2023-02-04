#include "pch.h"
#include "Shader.h"

namespace Engine3D
{
	Shader::Shader(unsigned int shaderType, const char* src)
	{
		id = glCreateShader(shaderType);
		std::string source = ReadSource(src);
		const char* csource = source.c_str();
		glShaderSource(id, 1, &csource, 0);
		glCompileShader(id);

		GLint success = 0;
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);
		if (success == GL_FALSE)
		{
			int length;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
			auto message = (char*)_malloca(length * sizeof(char));
			glGetShaderInfoLog(id, length, &length, message);
			std::cout << message << std::endl;
			glDeleteShader(id);
			delete(message);
		}
	}

	std::string Shader::ReadSource(const char* filePath) const
	{
		std::fstream file(filePath, std::ios::in);
		if (!file.is_open())
		{
			std::cout << filePath << "failed to open" << std::endl;
		}

		std::string content;
		std::string line = "";
		while (!file.eof())
		{
			std::getline(file, line);
			content.append(line + "\n");
		}
		file.close();
		return content;

		return nullptr;
	}
}