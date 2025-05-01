#include <format>

#include "VFXLayer.h"
#include "core/event/EventDispatcher.h"
#include "graphics/Mesh.h"
#include "utils.h"

#define BIND_EVENT_FN(x) std::bind(&VFXLayer::x, this, std::placeholders::_1)

void VFXLayer::OnEvent(core::event::Event& event)
{
	core::event::EventDispatcher dispatcher(event);
	dispatcher.Dispatch<core::event::MouseMovedEvent>(BIND_EVENT_FN(HandleMouseMovement));
	dispatcher.Dispatch<core::event::MouseLeaveEvent>(BIND_EVENT_FN(HandleMouseLeave));
}

void VFXLayer::OnUpdate(core::Timestep ts /*, pass Renderer class */)
{
	// do render stuff
	if (m_hoveredCell.has_value())
	{
		float width = 640.0f;
		float height = 480.0f;
		HoveredCell c = m_hoveredCell.value();
		float leftBound = utils::MapRangeLinearly((float)c.boundingRect.left, { 0.0f, width }, { -1.0f, 1.0f });
		float rightBound = utils::MapRangeLinearly((float)c.boundingRect.right, { 0.0f, width }, { -1.0f, 1.0f });
		float topBound = utils::MapRangeLinearly((float)c.boundingRect.top, { 0.0f, height }, { -1.0f, 1.0f });
		float bottomBound = utils::MapRangeLinearly((float)c.boundingRect.bottom, { 0.0f, height }, { -1.0f, 1.0f });

		gfx::Vertex tl = { { leftBound, -topBound, 0.0f } };
		gfx::Vertex bl = { { leftBound, -bottomBound, 0.0f } };
		gfx::Vertex tr = { { rightBound, -topBound, 0.0f } };
		gfx::Vertex br = { { rightBound, -bottomBound, 0.0f } };
		std::vector<gfx::Vertex> vertices = { tl, bl, tr, br };
		auto cellMesh = gfx::Mesh(vertices, { 0, 1, 2, 2, 1, 3 });

		GlCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		GlCall(glClear(GL_COLOR_BUFFER_BIT));

		cellMesh.Draw();
	}
}

bool VFXLayer::HandleMouseMovement(core::event::MouseMovedEvent& event)
{
	float mouseX = event.GetX();
	float mouseY = event.GetY();
	auto cellSize = m_conf.GetCellSize();

	int x = int(mouseX / cellSize);
	int y = int(mouseY / cellSize);

	if (!m_hoveredCell)
	{
		UpdateHoveredCell(x, y, cellSize);
	}
	else if (!IsHoveredCell(x, y))
	{
		// place previous hovered cell to fading queue
		UpdateHoveredCell(x, y, cellSize);
	}

	return true; // stop event propagation
}

bool VFXLayer::HandleMouseLeave(core::event::MouseLeaveEvent& event)
{
	m_hoveredCell = std::nullopt;
	m_logger.Log(std::format("Mouse left the window, cell hover removed.\n"));
	return true; // stop event propagation
}

void VFXLayer::UpdateHoveredCell(int x, int y, int cellSize)
{
	m_hoveredCell = HoveredCell{
		x, y,
		CalcBoundingRect(x, y, cellSize)
	};

	m_logger.Log(
		std::format("New hovered cell:\tx={} y={} left={} right={} top={} bottom={}\n",
			m_hoveredCell->x,
			m_hoveredCell->y,
			m_hoveredCell->boundingRect.left,
			m_hoveredCell->boundingRect.right,
			m_hoveredCell->boundingRect.top,
			m_hoveredCell->boundingRect.bottom)
	);
}

VFXLayer::BoundingRect VFXLayer::CalcBoundingRect(int x, int y, int cellSize) const
{
	return BoundingRect{
		int(x * cellSize),
		int((x + 1) * cellSize),
		int(y * cellSize),
		int((y + 1) * cellSize)
	};
}

bool VFXLayer::IsHoveredCell(int x, int y)
{
	return m_hoveredCell->x == x && m_hoveredCell->y == y;
}
