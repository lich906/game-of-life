#pragma once

#include "gfxpch.h"

#include "Program.h"

namespace gfx
{

class CurrentProgram
{
public:
	static void Set(const Program& program);
	static void Unset();
	static Program& Get();

private:
	CurrentProgram() = delete;

	static inline std::optional<Program> m_lightProgram;
};

} // namespace gfx
