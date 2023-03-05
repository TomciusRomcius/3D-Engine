#include "enpch.h"
#include "Mesh.h"

#define DSHADER_PATH(shader) ("../Engine/Shaders/" + std::string(shader)).c_str()


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
	void Mesh::LoadModel(const char* modelPath)
	{
		std::ifstream file;
		file.open(modelPath);
		if (!file.is_open())
		{
			EN_ERROR("Failed to load model: " + std::string(modelPath))
			return;
		}
		std::string line;


		std::vector<glm::vec3> r_vertices;
		std::vector<unsigned int> r_indices;
		std::vector<glm::vec2> r_texCoords;

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
				std::sscanf(line.c_str(), "v %f %f", &u, &v);
				r_texCoords.push_back({ u, v });
			}
			if (line[0] == 'f')
			{
				unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
				std::sscanf(line.c_str(), "f %u/%u/%u %u/%u/%u %u/%u/%u",
					&vertexIndex[0], &uvIndex[0], &normalIndex[0],
					&vertexIndex[1], &uvIndex[1], &normalIndex[1],
					&vertexIndex[2], &uvIndex[2], &normalIndex[2]);
				r_indices.push_back(vertexIndex[0] - 1);
				r_indices.push_back(vertexIndex[1] - 1);
				r_indices.push_back(vertexIndex[2] - 1);
				
			}
		}
		vertices = r_vertices;
		indices = r_indices;
		texCoords = r_texCoords;

		vbo.reset();
		ebo.reset();

		vbo = std::make_unique<VBO>(vertices, texCoords);
		ebo = std::make_unique<EBO>(indices);
		EN_INFO("Succesfully loaded model: " + std::string(modelPath))
	}
}
