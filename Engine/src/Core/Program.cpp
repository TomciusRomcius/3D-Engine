#include "enpch.h"
#include "Program.h"

namespace Engine3D
{
	Program::Program(Shader* vertexShader, Shader* fragmentShader)
	{
		id = glCreateProgram();
		glAttachShader(id, vertexShader->Id());
		glAttachShader(id, fragmentShader->Id());
		glLinkProgram(id);

		int status;
		glGetProgramiv(id, GL_LINK_STATUS, &status); // Success - 1, Failure - 0
		if (status == 0) {
			char buffer[512];
			glGetProgramInfoLog(id, 512, NULL, buffer);
			std::cout << "Failed to link program: " << buffer << std::endl;
		}
	}

	void Program::UseProgram() const
	{
		glUseProgram(id);
	}

	unsigned int Program::Id() const
	{
		return id;
	}
}
