#pragma once
#include "Log.h"
class ENGINE_API Texture
{
public:
	Texture(const char* path);
	~Texture();
	void Bind();
private:
	unsigned int id;
};

