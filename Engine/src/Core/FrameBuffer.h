#pragma once
#include "Log.h"
#include "Texture.h"
#include "RenderBuffer.h"

namespace Engine3D
{
	class ENGINE_API Framebuffer
	{
	public:
		Framebuffer();
		~Framebuffer();
		inline void Bind() { 
			glBindFramebuffer(GL_FRAMEBUFFER, id);
		};
		inline void Unbind() { 
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		};
		inline unsigned int Id() { return id; };
		inline unsigned int TextureId() { return texture.Id(); };
		inline unsigned int RenderBufferId() { return renderBuffer.Id(); };
	private:
		unsigned int id;
		Texture texture;
		RenderBuffer renderBuffer;
	};
}
