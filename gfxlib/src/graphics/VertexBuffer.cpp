#include "gfxpch.h"

#include "graphics/VertexBuffer.h"

using namespace gfx;

VertexBuffer::VertexBuffer()
	: m_size(0)
{
	GlCall(gc.Create(m_obj, glGenBuffers, glDeleteBuffers));
}

VertexBuffer::VertexBuffer(const VertexBuffer& other)
	: m_size(other.m_size)
{
	gc.Copy(other.m_obj, m_obj);
}

VertexBuffer::VertexBuffer(const void* data, size_t size, GLenum usage)
	: m_size(size)
{
	GlCall(gc.Create(m_obj, glGenBuffers, glDeleteBuffers));
	SetData(data, m_size, usage);
	Unbind();
}

VertexBuffer::~VertexBuffer()
{
	GlCall(gc.Destroy(m_obj));
}

VertexBuffer::operator GLuint() const
{
	return m_obj;
}

const VertexBuffer& VertexBuffer::operator=(const VertexBuffer& other)
{
	gc.Copy(other.m_obj, m_obj, true);
	return *this;
}

void VertexBuffer::Bind() const
{
	GlCall(glBindBuffer(GL_ARRAY_BUFFER, m_obj));
}

void VertexBuffer::Unbind() const
{
	GlCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

size_t VertexBuffer::GetSize() const
{
	return m_size;
}

void VertexBuffer::SetData(const void* data, size_t size, GLenum usage)
{
	Bind();
	GlCall(glBufferData(GL_ARRAY_BUFFER, size, data, usage));
	m_size = size;
}

void VertexBuffer::SetSubData(const void* data, size_t offset, size_t size)
{
	if (size > m_size)
	{
		throw std::logic_error("Data size exceeds current buffer size.");
	}

	Bind();
	GlCall(glBufferSubData(GL_ARRAY_BUFFER, offset, size, data));
}

void VertexBuffer::GetSubData(void* data, size_t offset, size_t size) const
{
	Bind();
	GlCall(glGetBufferSubData(GL_ARRAY_BUFFER, offset, size, data));
}
