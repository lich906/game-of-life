#pragma once

#include "gfxpch.h"

namespace gfx
{

class VertexBuffer
{
public:
	VertexBuffer();
	VertexBuffer(const VertexBuffer& other);
	VertexBuffer(const void* data, size_t size, GLenum usage);

	~VertexBuffer();

	operator GLuint() const;
	const VertexBuffer& operator=(const VertexBuffer& other);

	void Bind() const;
	void Unbind() const;

	size_t GetSize() const;

	void SetData(const void* data, size_t size, GLenum usage);
	void SetSubData(const void* data, size_t offset, size_t size);

	void GetSubData(void* data, size_t offset, size_t size) const;

private:
	static inline GL::GC gc;
	GLuint m_obj;
	size_t m_size;
};

} // namespace gfx
