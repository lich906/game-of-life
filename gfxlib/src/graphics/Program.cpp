#include "gfxpch.h"

#include "graphics/Program.h"

using namespace gfx;

Program::Program()
{
	GlCall(m_obj = gc.Create(glCreateProgram(), glDeleteProgram));
}

Program::Program(const Program& other)
{
	gc.Copy(other.m_obj, m_obj);
}

Program::Program(const Shader& vertex)
	: Program()
{
	GlCall(glAttachShader(m_obj, vertex));
	Link();
}

Program::Program(const Shader& vertex, const Shader& fragment)
	: Program()
{
	GlCall(glAttachShader(m_obj, vertex));
	GlCall(glAttachShader(m_obj, fragment));
	Link();
}

Program::Program(const Shader& vertex, const Shader& fragment, const Shader& geometry)
	: Program()
{
	GlCall(glAttachShader(m_obj, vertex));
	GlCall(glAttachShader(m_obj, fragment));
	GlCall(glAttachShader(m_obj, geometry));
	Link();
}

Program::Program(const std::string& vertexPath)
	: Program(Shader(GL_VERTEX_SHADER, vertexPath))
{
}

Program::Program(const std::string& vertexPath, const std::string& fragmentPath)
	: Program(Shader(GL_VERTEX_SHADER, vertexPath), Shader(GL_FRAGMENT_SHADER, fragmentPath))
{
}

Program::Program(const std::string& vertexPath, const std::string& fragmentPath, const std::string& geometryPath)
	: Program(Shader(GL_VERTEX_SHADER, vertexPath), Shader(GL_FRAGMENT_SHADER, fragmentPath), Shader(GL_GEOMETRY_SHADER, geometryPath))
{
}

Program::~Program()
{
	GlCall(gc.Destroy(m_obj));
}

Program::operator GLuint() const
{
	return m_obj;
}

const Program& Program::operator=(const Program& other)
{
	gc.Copy(other.m_obj, m_obj, true);
	return *this;
}

void Program::Use()
{
	GlCall(glUseProgram(m_obj));
}

void Program::SetUniform1i(const std::string& name, int value)
{
	m_container.Set(name, value);
	GlCall(glUniform1i(GetUniformLocation(name), value));
}

void gfx::Program::SetUniform1f(const std::string& name, float value)
{
	m_container.Set(name, value);
	GlCall(glUniform1f(GetUniformLocation(name), value));
}

void gfx::Program::SetUniform4fv(const std::string& name, const glm::vec4& v)
{
	m_container.Set(name, v);
	GlCall(glUniform4fv(GetUniformLocation(name), 1, glm::value_ptr(v)));
}

void gfx::Program::SetUniform3fv(const std::string& name, const glm::vec3& v)
{
	m_container.Set(name, v);
	GlCall(glUniform3fv(GetUniformLocation(name), 1, glm::value_ptr(v)));
}

void Program::SetUniformMatrix4fv(const std::string& name, const glm::mat4& mat)
{
	m_container.Set(name, mat);
	GlCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(mat)));
}

void Program::Link() const
{
	GLint res;

	GlCall(glLinkProgram(m_obj));
	GlCall(glGetProgramiv(m_obj, GL_LINK_STATUS, &res));

	if (res == GL_FALSE)
	{
		throw std::runtime_error(GetInfoLog());
	}
}

std::string Program::GetInfoLog() const
{
	GLint res;
	GlCall(glGetProgramiv(m_obj, GL_INFO_LOG_LENGTH, &res));

	if (res > 0)
	{
		std::string infoLog(res, 0);
		GlCall(glGetProgramInfoLog(m_obj, res, &res, &infoLog[0]));
		return infoLog;
	}
	else
	{
		return "";
	}
}

GLint Program::GetAttributeLocation(const std::string& name) const
{
	GlCall(GLint loc = glGetAttribLocation(m_obj, name.c_str()));

	if (loc == -1)
	{
		throw std::runtime_error(
			"The '" + name + "' attribute variable is not an active attribute in the specified program object "
			"or name starts with the reserved prefix 'gl_'");
	}

	return loc;
}

GLint Program::GetUniformLocation(const std::string& name) const
{
	GlCall(GLint loc = glGetUniformLocation(m_obj, name.c_str()));

	if (loc == -1)
	{
		throw std::runtime_error(
			"Name '" + name + "' does not correspond to an active uniform variable "
			"in program or name starts with the reserved prefix 'gl_'");
	}

	return loc;
}
