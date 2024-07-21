#pragma once
#include "IComponent.h"
#include "../Core/VertexArray.h"
#include "../Core/BufferElement.h"

namespace Engine3D
{
	struct ENGINE_API Mesh : public IComponent
	{
	public:
		void Start() override;
		void Update() override;
		void SetVertices(const std::vector<float>& _vertices)
		{

		}
		void LoadModel(const char* modelPath);
		std::unique_ptr<VBO> vbo;
		std::unique_ptr<VertexArray> vao;
		std::unique_ptr<EBO> ebo;
		std::vector<glm::vec3> vertices;
		std::vector<unsigned int> indices;
		std::vector<glm::vec2> texCoords;
		std::vector<glm::vec3> normals;
		std::string GetLoadedModel() { return loadedModel; }
	private:
		std::string loadedModel = "";
	};
}
