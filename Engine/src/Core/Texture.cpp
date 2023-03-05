#include "enpch.h"
#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(const char* path)
{
	glGenTextures(1, &id);
	EN_TRACE("Creating a texture id = " + std::to_string(id));

	glBindTexture(GL_TEXTURE_2D, id);

	int width, height, channels;
	unsigned char* data = stbi_load(path, &width, &height, &channels, 0);
	if (!data)
	{
		EN_ERROR("Failed to locate image:" + std::string(path))
		return;
	}

	GLenum format{};
	switch (channels)
	{
	case 1:
		format = GL_RED;
		break;
	case 3:
		format = GL_RGB;
		break;
	case 4:
		format = GL_RGBA;
		break;
	default:
		EN_ERROR("Failed to load image:" + std::string(path))
			return;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	stbi_image_free(data);
	EN_INFO("Succesfully loaded texture: " + std::string(path))


}

Texture::~Texture()
{
	EN_TRACE("Deleting texture: " + std::to_string(id));
	glDeleteTextures(1, &id);
}

void Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, id);
}
