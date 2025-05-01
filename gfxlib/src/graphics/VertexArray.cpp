#include "gfxpch.h"

#include "graphics/VertexArray.h"

using namespace gfx;

VertexArray::VertexArray()
{
	GlCall(gc.Create(m_obj, glGenVertexArrays, glDeleteVertexArrays));
}

VertexArray::VertexArray(const VertexArray& other)
{
	gc.Copy(other.m_obj, m_obj);
}

VertexArray::~VertexArray()
{
	gc.Destroy(m_obj);
}

void VertexArray::Bind() const
{
	GlCall(glBindVertexArray(m_obj));
}

void VertexArray::Unbind() const
{
	GlCall(glBindVertexArray(0));
}

VertexArray::operator GLuint() const
{
	return m_obj;
}

const VertexArray& VertexArray::operator=(const VertexArray& other)
{
	gc.Copy(other.m_obj, m_obj, true);
	return *this;
}

void VertexArray::BindAttribute(GLint location, GLenum type, GLuint count, GLuint stride, intptr_t offset) const
{
	GlCall(glVertexAttribPointer(location, count, type, GL_FALSE, stride, (const GLvoid*)offset));
	GlCall(glEnableVertexAttribArray(location));
}
