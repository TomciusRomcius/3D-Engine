#include "../pch.h"
#include "MeshRenderer.h"

namespace Engine3D
{
	void MeshRenderer::Start()
	{
		// Initialize default program

		vertexShader = std::make_unique<Shader>(GL_VERTEX_SHADER, "src/shaders/vertex.shader");
		fragmentShader = std::make_unique<Shader>(GL_FRAGMENT_SHADER, "src/shaders/fragment.shader");
		program = std::make_unique<Program>(vertexShader.get(), fragmentShader.get());
	}

	void MeshRenderer::Update()
	{
		program->UseProgram();
		SetShaderUniforms();
		this->object->GetComponent<Mesh>().vbo->Bind();
		this->object->GetComponent<Mesh>().ebo->Bind();
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
	}

	void MeshRenderer::SetShaderUniforms()
	{
		int mvpLoc = glGetUniformLocation(program->Id(), "mvp");
		if (mvpLoc == -1) return;
		
		glUniformMatrix4fv(mvpLoc, 1, false, glm::value_ptr(this->object->GetComponent<Transform>().Mvp()));
	}
}