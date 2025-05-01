#include <iostream>
#include "core/core.h"
#include "corecrt_math_defines.h"

#include "Config.h"
#include "VFXLayer.h"

int main()
{
	std::unique_ptr<core::Application> app = std::make_unique<core::Application>("Game of life", 640, 480);
	Config conf;
	Logger logger;
	std::shared_ptr<core::Layer> vfxLayer = std::make_shared<VFXLayer>(conf, logger);
	app->PushOverlay(vfxLayer);
	app->Run();
}
