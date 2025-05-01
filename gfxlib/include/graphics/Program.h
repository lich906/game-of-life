#pragma once

#include "gfxpch.h"

#include "Shader.h"
#include "UniformContainer.h"

namespace gfx
{

class Program
{
public:
	Program(const Program& other);
	Program(const Shader& vertex);
	Program(const Shader& vertex, const Shader& fragment);
	Program(const Shader& vertex, const Shader& fragment, const Shader& geometry);
	Program(const std::string& vertexPath);
	Program(const std::string& vertexPath, const std::string& fragmentPath);
	Program(const std::string& vertexPath, const std::string& fragmentPath, const std::string& geometryPath);

	~Program();

	operator GLuint() const;
	const Program& operator=(const Program& other);

	void Use();

	void SetUniform1i(const std::string& name, int value);
	void SetUniform1f(const std::string& name, float value);
	void SetUniform4fv(const std::string& name, const glm::vec4& v);
	void SetUniform3fv(const std::string& name, const glm::vec3& v);
	void SetUniformMatrix4fv(const std::string& name, const glm::mat4& mat);

	inline const UniformContainer& GetUniformContainer() const { return m_container; }

private:
	Program();
	void Link() const;
	std::string GetInfoLog() const;

	GLint GetAttributeLocation(const std::string& name) const;
	GLint GetUniformLocation(const std::string& name) const;

	static inline GL::GC gc;
	GLuint m_obj;
	UniformContainer m_container;
};

} // namespace gfx
