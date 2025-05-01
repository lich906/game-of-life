#pragma once

#include "gfxpch.h"

class UniformContainer
{
public:
	void Set(const std::string& name, int val);
	void Set(const std::string& name, float val);
	void Set(const std::string& name, const glm::vec4& val);
	void Set(const std::string& name, const glm::vec3& val);
	void Set(const std::string& name, const glm::mat4& val);

	template <typename T>
	T Get(const std::string& name) const { return T(); };

// clang-format off
	template <>
	int Get<int>(const std::string& name) const
	{
		if (m_intUniforms.contains(name)) return m_intUniforms.at(name);
		throw std::runtime_error("Uniform '" + name + "' was not set.");
	}

	template<>
	float Get<float>(const std::string& name) const
	{
		if (m_floatUniforms.contains(name)) return m_floatUniforms.at(name);
		throw std::runtime_error("Uniform '" + name + "' was not set.");
	}

	template <>
	glm::vec4 Get<glm::vec4>(const std::string& name) const
	{
		if (m_vec4Uniforms.contains(name)) return m_vec4Uniforms.at(name);
		throw std::runtime_error("Uniform '" + name + "' was not set.");
	}

	template <>
	glm::vec3 Get<glm::vec3>(const std::string& name) const
	{
		if (m_vec3Uniforms.contains(name)) return m_vec3Uniforms.at(name);
		throw std::runtime_error("Uniform '" + name + "' was not set.");
	}

	template <>
	glm::mat4 Get<glm::mat4>(const std::string& name) const
	{
		if (m_mat4Uniforms.contains(name)) return m_mat4Uniforms.at(name);
		throw std::runtime_error("Uniform '" + name + "' was not set.");
	}
	// clang-format on
private:
	std::unordered_map<std::string, int> m_intUniforms;
	std::unordered_map<std::string, float> m_floatUniforms;
	std::unordered_map<std::string, glm::vec4> m_vec4Uniforms;
	std::unordered_map<std::string, glm::vec3> m_vec3Uniforms;
	std::unordered_map<std::string, glm::mat4> m_mat4Uniforms;
};
