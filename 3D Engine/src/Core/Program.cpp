#include "../pch.h"
#include "Program.h"

namespace Engine3D
{
	Program::Program(Shader* vertexShader, Shader* fragmentShader)
	{
		id = glCreateProgram();
		glAttachShader(id, vertexShader->Id());
		glAttachShader(id, fragmentShader->Id());
		glLinkProgram(id);
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
