#pragma once

#include "gfxpch.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace gfx
{

class VertexArray
{
public:
	VertexArray();
	VertexArray(const VertexArray& other);

	~VertexArray();

	void Bind() const;
	void Unbind() const;

	operator GLuint() const;
	const VertexArray& operator=(const VertexArray& other);

	void BindAttribute(GLint location, GLenum type, GLuint count, GLuint stride, intptr_t offset) const;

private:
	static inline GL::GC gc;
	GLuint m_obj;
};

} // namespace gfx
