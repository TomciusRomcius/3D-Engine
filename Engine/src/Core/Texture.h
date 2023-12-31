#pragma once
#include "Log.h"
class ENGINE_API Texture
{
public:
	Texture(const char* path);
	Texture(); // For framebuffer
	~Texture();
	inline void Bind() { glBindTexture(GL_TEXTURE_2D, id); };
	inline unsigned int Id() { return id; };
private:
	unsigned int id;
};

