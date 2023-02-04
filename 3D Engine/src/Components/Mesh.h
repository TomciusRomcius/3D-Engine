#pragma once
#include "IComponent.h"

namespace Engine3D
{
	struct Mesh : public IComponent
	{
	public:
		void Start();
		void Update();
		void SetVertices(const std::vector<float>& _vertices)
		{

		}
		std::unique_ptr<VBO> vbo;
		std::unique_ptr<EBO> ebo;
		std::vector<glm::vec3> vertices;
		std::vector<float> texCoords;
		std::vector<float> normals;
	};
}
