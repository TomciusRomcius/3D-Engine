#include "enpch.h"
#include "Mesh.h"

#define DSHADER_PATH(shader) ("../Engine/Shaders/" + std::string(shader)).c_str()
#define MODEL_PATH(model) ("../Resources/Models/" + std::string(model)).c_str()

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
		auto vertxBuffer = BufferElement(vertices.data(), BufferDataType::Float, vertices.size(), 3, false);
		std::vector<BufferElement> elements = { vertxBuffer };
		vbo = std::make_unique<VBO>(elements);
		vao = std::make_unique<VertexArray>(elements);
		ebo = std::make_unique<EBO>(indices);
	}

	void Mesh::Update()
	{
		
	}
	void Mesh::LoadModel(const char* modelPath)
	{
		vertices.clear();
		texCoords.clear();
		indices.clear();
		normals.clear();

		std::ifstream file;
		file.open(MODEL_PATH(modelPath));
		if (!file.is_open())
		{
			EN_ERROR("Failed to load model: " + std::string(modelPath))
			return;
		}

		loadedModel = modelPath;

		std::string line;
		std::vector<glm::vec3> r_vertices;
		std::vector<glm::vec2> r_texCoords;
		std::vector<glm::vec3> r_normals;
		std::vector<unsigned int> v_indices;
		std::vector<unsigned int> uv_indices;
		std::vector<unsigned int> n_indices;
		while (std::getline(file, line))
		{
			if (line[0] == 'v' && line[1] == ' ')
			{
				float x, y, z;
				std::sscanf(line.c_str(), "v %f %f %f", &x, &y, &z);
				r_vertices.push_back({ x, y, z });
			}
			if (line[0] == 'v' && line[1] == 't')
			{
				float u, v;
				std::sscanf(line.c_str(), "vt %f %f", &u, &v);
				r_texCoords.push_back({ u, v });
			}

			if (line[0] == 'v' && line[1] == 'n')
			{
				float x, y, z;
				std::sscanf(line.c_str(), "vn %f %f %f", &x, &y, &z);
				r_normals.push_back({ x, y, z });
			}

			if (line[0] == 'f')
			{
				unsigned int vertexIndex[4], uvIndex[4], normalIndex[4];
				std::sscanf(line.c_str(), "f %u/%u/%u %u/%u/%u %u/%u/%u",
					&vertexIndex[0], &uvIndex[0], &normalIndex[0],
					&vertexIndex[1], &uvIndex[1], &normalIndex[1],
					&vertexIndex[2], &uvIndex[2], &normalIndex[2]);

				v_indices.push_back(vertexIndex[0] - 1);
				v_indices.push_back(vertexIndex[1] - 1);
				v_indices.push_back(vertexIndex[2] - 1);

				uv_indices.push_back(uvIndex[0] - 1);
				uv_indices.push_back(uvIndex[1] - 1);
				uv_indices.push_back(uvIndex[2] - 1);

				n_indices.push_back(normalIndex[0] - 1);
				n_indices.push_back(normalIndex[1] - 1);
				n_indices.push_back(normalIndex[2] - 1);

			}
		}
		file.close();
		for (auto& vIndex : v_indices)
		{
			vertices.push_back(r_vertices[vIndex]);
		}

		for (auto& uvIndex : uv_indices)
		{
			texCoords.push_back(r_texCoords[uvIndex]);
		}

		for (auto& nIndex : n_indices)
		{
			normals.push_back(r_normals[nIndex]);
		}

		vbo.reset();
		ebo.reset();

		auto vertBuffer = BufferElement(vertices.data(), BufferDataType::Float, vertices.size(), 3, false);
		auto texBuffer = BufferElement(texCoords.data(), BufferDataType::Float, texCoords.size(), 2, false);
		auto normBuffer = BufferElement(normals.data(), BufferDataType::Float, normals.size(), 3, false);
		std::vector<BufferElement> elements = { vertBuffer, texBuffer, normBuffer };
		vbo = std::make_unique<VBO>(elements);
		vao = std::make_unique<VertexArray>(elements);
		EN_INFO("Succesfully loaded model: " + std::string(modelPath))
	}
}
