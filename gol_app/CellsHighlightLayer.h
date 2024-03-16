#pragma once

#include <optional>

#include "core/core.h"
#include "Configuration.h"
#include "core/event/MouseEvent.h"
#include "Logger.h"

class CellsHighlightLayer : public core::Layer
{
public:
	CellsHighlightLayer(Configuration& conf, Logger& logger)
		: Layer("CellsHighlightLayer"),
		m_conf(conf),
		m_logger(logger) {};

	void OnEvent(core::event::Event& event) override;

private:
	struct BoundingRect
	{
		int left;
		int right;
		int top;
		int bottom;
	};
	struct HoveredCell
	{
		int x, y;
		BoundingRect boundingRect;
	};

	bool HandleMouseMovement(core::event::MouseMovedEvent& event);
	bool HandleMouseLeave(core::event::MouseLeaveEvent& event);
	void UpdateHoveredCell(int x, int y, int cellSize);
	bool IsHoveredCell(int x, int y);
	BoundingRect CalcBoundingRect(int x, int y, int cellSize) const;

	std::optional<HoveredCell> m_hoveredCell;
	Configuration& m_conf;
	Logger& m_logger;
};
