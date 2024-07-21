#pragma once
#include "Log.h"

class RenderBuffer
{
public:
	RenderBuffer();
	~RenderBuffer();
	inline void Bind() { glBindRenderbuffer(GL_RENDERBUFFER, id); };
	inline void Unbind() { glBindRenderbuffer(GL_RENDERBUFFER, 0); };
	inline unsigned int Id() { return id; };
private:
	unsigned int id;
};

