#include "enpch.h"
#include "FrameBuffer.h"

namespace Engine3D {
	Framebuffer::Framebuffer()
		: texture(), renderBuffer(), id(0)
	{
		glGenFramebuffers(1, &id);
		glBindFramebuffer(GL_FRAMEBUFFER, id);
		
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture.Id(), 0);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBuffer.Id());

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
			EN_ERROR("ERROR::FRAMEBUFFER:: Framebuffer is not complete!");
			return;
		}
		glBindFramebuffer(GL_FRAMEBUFFER, 0); // Unbind framebuffer
		EN_INFO("Succesfully a framebuffer id = " + std::to_string(id));
	}
	Engine3D::Framebuffer::~Framebuffer()
	{
		glDeleteFramebuffers(1, &id);
	}
}
