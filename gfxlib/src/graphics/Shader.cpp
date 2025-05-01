#include "gfxpch.h"

#include "graphics/Shader.h"

using namespace gfx;

Shader::Shader(GLenum type, const std::string& sourcePath)
	: m_type(type)
{
	GlCall(m_obj = gc.Create(glCreateShader(type), glDeleteShader));

	std::string source;
	std::ifstream file;
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		file.open(sourcePath);
		std::stringstream ss;
		ss << file.rdbuf();
		file.close();
		source = ss.str();
	}
	catch (std::ifstream::failure&)
	{
		throw std::runtime_error("Failed to read shader source: " + sourcePath);
	}

	SetSource(source);
	Compile();
}

Shader::Shader(const Shader& other)
	: m_type(other.m_type)
{
	gc.Copy(other.m_obj, m_obj);
}

Shader::~Shader()
{
	GlCall(gc.Destroy(m_obj));
}

Shader::operator GLuint() const
{
	return m_obj;
}

Shader& Shader::operator=(const Shader& other)
{
	gc.Copy(other.m_obj, m_obj, true);
	return *this;
}

GLenum Shader::GetType() const
{
	return m_type;
}

void Shader::SetSource(const std::string& source) const
{
	auto c = source.c_str();
	GlCall(glShaderSource(m_obj, 1, &c, NULL));
}

void Shader::Compile() const
{
	GLint res;

	glCompileShader(m_obj);
	glGetShaderiv(m_obj, GL_COMPILE_STATUS, &res);

	if (res == GL_FALSE)
		throw std::runtime_error(GetInfoLog());
}

std::string Shader::GetInfoLog() const
{
	GLint res;
	glGetShaderiv(m_obj, GL_INFO_LOG_LENGTH, &res);

	if (res > 0)
	{
		std::string infoLog(res, 0);
		glGetShaderInfoLog(m_obj, res, &res, &infoLog[0]);
		return infoLog;
	}
	else
	{
		return "";
	}
}
