#include "enpch.h"
#include "MeshRenderer.h"

namespace Engine3D
{
	void MeshRenderer::Start()
	{
		// Initialize default program

		vertexShader = std::make_unique<Shader>(GL_VERTEX_SHADER, "vertex.shader");
		fragmentShader = std::make_unique<Shader>(GL_FRAGMENT_SHADER, "fragment.shader");
		program = std::make_unique<Program>(vertexShader.get(), fragmentShader.get());
		texture = std::make_unique<Texture>("../Textures/brick.jpg");
	}

	void MeshRenderer::Update()
	{
		
		program->UseProgram();
		texture->Bind();
		SetShaderUniforms();
		this->object->GetComponent<Mesh>().vbo->Bind();
		this->object->GetComponent<Mesh>().ebo->Bind();
		int i = this->object->GetComponent<Mesh>().indices.size();
		glDrawElements(GL_TRIANGLES, this->object->GetComponent<Mesh>().indices.size(), GL_UNSIGNED_INT, nullptr);
		
	}

	void MeshRenderer::SetShaderUniforms()
	{
		int mvpLoc = glGetUniformLocation(program->Id(), "mvp");
		if (mvpLoc == -1) return;
		
		glUniformMatrix4fv(mvpLoc, 1, false, glm::value_ptr(this->object->GetComponent<Transform>().Mvp()));
	}
}