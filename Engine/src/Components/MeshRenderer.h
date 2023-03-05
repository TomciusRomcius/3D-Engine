#pragma once
#include "../Core/Program.h"
#include "Mesh.h"
#include "Transform.h"
#include "../Core/Texture.h"

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
		std::unique_ptr<Texture> texture;
		std::unique_ptr<Program> program;
		glm::vec3 color;
	};
}
