#include <iostream>
#include "core/core.h"
#include "corecrt_math_defines.h"

#include "CellsHighlightLayer.h"

int main()
{
	std::unique_ptr<core::Application> app = std::make_unique<core::Application>("Game of life", 640, 480);
	Configuration conf;
	Logger logger;
	std::shared_ptr<core::Layer> cellsHighlightLayer = std::make_shared<CellsHighlightLayer>(conf, logger);
	app->PushOverlay(cellsHighlightLayer);
	app->Run();
}
