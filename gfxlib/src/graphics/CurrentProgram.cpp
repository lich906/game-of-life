#include "gfxpch.h"

#include "graphics/CurrentProgram.h"

using namespace gfx;

void CurrentProgram::Set(const Program& program)
{
	m_lightProgram = program;
}

void CurrentProgram::Unset()
{
	m_lightProgram.reset();
}

Program& CurrentProgram::Get()
{
	if (m_lightProgram)
	{
		return *m_lightProgram;
	}

	throw std::logic_error("Current program was not set.");
}
