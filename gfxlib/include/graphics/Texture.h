#pragma once

#include "gfxpch.h"

namespace gfx
{

class Texture
{
public:
	Texture(
		const std::string& filePath,
		GLint wrappingMode = GL_CLAMP_TO_EDGE,
		GLint minFilteringMode = GL_LINEAR_MIPMAP_LINEAR,
		GLint magFilteringMode = GL_LINEAR);

	~Texture();

	Texture(const Texture& other);
	Texture& operator=(const Texture& other);

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	int GetWidth() const;
	int GetHeight() const;

private:
	static inline GL::GC gc;

	GLuint m_rendererId;
	std::string m_filePath;
	unsigned char* m_localBuffer;
	int m_width, m_height, m_bpp; // bytes per pixel
};

} // namespace gfx
