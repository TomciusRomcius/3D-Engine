#include "enpch.h"
#include "RenderBuffer.h"

RenderBuffer::RenderBuffer()
	: id(0)
{
	glGenRenderbuffers(1, &id);
	glBindRenderbuffer(GL_RENDERBUFFER, id);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 1280, 720);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	EN_INFO("Created a renderbuffer id = " + std::to_string(id));
}

RenderBuffer::~RenderBuffer()
{
	glDeleteRenderbuffers(1, &id);
	EN_INFO("Deleted a renderbuffer id = " + std::to_string(id));
}
