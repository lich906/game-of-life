#pragma once

#include "gfxpch.h"

namespace gfx
{

class Shader
{
public:
	// @throw std::runtime_error : On compile error or on file buffer read
	Shader(GLenum type, const std::string& sourcePath);
	Shader(const Shader& other);

	~Shader();

	operator GLuint() const;
	Shader& operator=(const Shader& other);

	GLenum GetType() const;

private:
	void SetSource(const std::string& source) const;
	void Compile() const;
	std::string GetInfoLog() const;

	static inline GL::GC gc;
	GLuint m_obj;
	const GLenum m_type;
};

} // namespace gfx
