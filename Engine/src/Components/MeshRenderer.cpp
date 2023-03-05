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
	}

	void MeshRenderer::Update()
	{
		if (texture != nullptr) texture->Bind();

		program->UseProgram();
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
		int colorLoc = glGetUniformLocation(program->Id(), "color");
		if (colorLoc == -1) return;

		glUniformMatrix4fv(mvpLoc, 1, false, glm::value_ptr(this->object->GetComponent<Transform>().Mvp()));
		glUniform4f(colorLoc, color.x, color.y, color.z, 1);
	}
}