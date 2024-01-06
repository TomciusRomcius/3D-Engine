#include "enpch.h"
#include "Shader.h"

#ifdef DIST
	#define DSHADER_PATH(shader) ("Shaders/" + std::string(shader)).c_str()
#else
	#define DSHADER_PATH(shader) ("../Resources/Shaders/" + std::string(shader)).c_str()
#endif

namespace Engine3D
{
	Shader::Shader(unsigned int shaderType, const char* src)
	{
		id = glCreateShader(shaderType);
		std::string source = ReadSource(DSHADER_PATH(src));
		const char* csource = source.c_str();
		glShaderSource(id, 1, &csource, 0);
		glCompileShader(id);

		GLint success = 0;
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);
		if (success == GL_FALSE)
		{
			EN_ERROR("Failed to compile shader: " + std::string(src))
			int length;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
			std::vector<char> message(length);
			glGetShaderInfoLog(id, length, &length, &message[0]);
			for (char c : message)
				std::cout << c;
			glDeleteShader(id);
		}
	}

	std::string Shader::ReadSource(const char* filePath) const
	{
		std::fstream file(filePath, std::ios::in);
		if (!file.is_open())
		{
			std::cout << "Failed to load shader: " << filePath << std::endl;
			return "err";
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