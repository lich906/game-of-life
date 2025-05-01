#pragma once

#include "gfxpch.h"

#include "TexCoords.h"

namespace gfx
{

struct Vertex
{
	using Position = glm::vec3;
	using Normal = glm::vec3;
	using Color = glm::vec4;
	using TexCoords = glm::vec2;

	Position position;
	Normal normal;
	Color color;
	TexCoords texCoords;
};

} // namespace gfx
