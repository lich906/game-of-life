#include "gfxpch.h"

#include "graphics/Mesh.h"

using namespace gfx;

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices, GLenum usage)
{
	// Bind the Vertex Array Object first, then bind and set vertex and index buffer(s) and attribute pointer(s).
	m_vertexArray.Bind();

	m_vertexBuffer.Bind();
	m_vertexBuffer.SetData(vertices.data(), vertices.size() * sizeof(Vertex), usage);

	m_indexBuffer.Bind();
	m_indexBuffer.SetData(indices.data(), indices.size() * sizeof(GLuint), usage);

	GLsizei stride = sizeof(Vertex);

	// Position attribute
	m_vertexArray.BindAttribute(0, GL_FLOAT, sizeof(Vertex::Position) / sizeof(float), stride, 0);

	// Normal attribute
	m_vertexArray.BindAttribute(1, GL_FLOAT, sizeof(Vertex::Normal) / sizeof(float), stride, sizeof(Vertex::Position));

	// Color coords attribute
	m_vertexArray.BindAttribute(2, GL_FLOAT, sizeof(Vertex::Color) / sizeof(float), stride, sizeof(Vertex::Position) + sizeof(Vertex::Normal));

	// Tex coords attribute
	m_vertexArray.BindAttribute(3, GL_FLOAT, sizeof(Vertex::TexCoords) / sizeof(float), stride, sizeof(Vertex::Position) + sizeof(Vertex::Normal) + sizeof(Vertex::Color));

	m_vertexBuffer.Unbind();

	// ! Do not unbind m_indexBuffer !

	m_vertexArray.Unbind();
}

void Mesh::Draw(GLenum mode) const
{
	m_vertexArray.Bind();
	GlCall(glDrawElements(mode, (int)m_indexBuffer.GetSize(), GL_UNSIGNED_INT, 0));
}
