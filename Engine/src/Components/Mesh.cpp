#include "enpch.h"
#include "Mesh.h"

namespace Engine3D
{
	void Mesh::Start()
	{
		// Default triangle
		vertices =
		{
			{ -1.f, -1.f, .0f},
			{.0f, 1.f, .0f },
			{1.f, -1.f, .0f}
		};
		std::vector<unsigned int> indices = { 0, 1, 2 };
		// Create a vbo and ebo
		vbo = std::make_unique<VBO>(vertices);
		ebo = std::make_unique<EBO>(indices);
	}

	void Mesh::Update()
	{

	}
}
