#pragma once
#include "../Core/Program.h"
#include "Mesh.h"
#include "Transform.h"

namespace Engine3D
{
	struct ENGINE_API MeshRenderer : public IComponent
	{
	public:
		void Start();

		void Update(); // Draw the object

		void SetShaderUniforms();
		std::unique_ptr<Shader> vertexShader;
		std::unique_ptr<Shader> fragmentShader;

		std::unique_ptr<Program> program;
	};
}
