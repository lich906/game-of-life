#include "gfxpch.h"

#include "graphics/UniformContainer.h"

void UniformContainer::Set(const std::string& name, int val)
{
	m_intUniforms[name] = val;
}

void UniformContainer::Set(const std::string& name, float val)
{
	m_floatUniforms[name] = val;
}

void UniformContainer::Set(const std::string& name, const glm::vec4& val)
{
	m_vec4Uniforms[name] = val;
}

void UniformContainer::Set(const std::string& name, const glm::vec3& val)
{
	m_vec3Uniforms[name] = val;
}

void UniformContainer::Set(const std::string& name, const glm::mat4& val)
{
	m_mat4Uniforms[name] = val;
}
