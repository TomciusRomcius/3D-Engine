#pragma once
#include "Shader.h"

namespace Engine3D
{
	class Program
	{
	public:
		Program(Shader* vertexShader, Shader* fragmentShader);
		void UseProgram() const;
		unsigned int Id() const;
	private:
		unsigned int id;
	};
}
