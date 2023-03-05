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
			std::cout << "Failed to load model: " << modelPath;
			return;
		}
		std::string line;


		std::vector<glm::vec3> r_vertices;
		std::vector<unsigned int> r_indices;

		while (std::getline(file, line))
		{
			if (line[0] == 'v')
			{
				float x, y, z;
				std::sscanf(line.c_str(), "v %f %f %f", &x, &y, &z);
				r_vertices.push_back({ x, y, z });
			}
			if (line[0] == 'f')
			{
				unsigned int f1, f2, f3;
				std::sscanf(line.c_str(), "f %u %u %u", &f1, &f2, &f3);
				r_indices.push_back(f1 - 1);
				r_indices.push_back(f2 - 1);
				r_indices.push_back(f3 - 1);
			}
		}
		vertices = r_vertices;
		indices = r_indices;

		vbo.reset();
		ebo.reset();

		vbo = std::make_unique<VBO>(vertices);
		ebo = std::make_unique<EBO>(indices);
	}
}
