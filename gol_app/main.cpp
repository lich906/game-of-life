#include <iostream>
#include "core/core.h"
#include "corecrt_math_defines.h"

#include "CellsHighlightLayer.h"

//class rgbtriangle : public core::layer
//{
//public:
//	void onupdate(core::timestep ts) override
//	{
//		float x0 = 0;
//		float y0 = 0;
//		glbegin(gl_lines);
//		for (int angle = 0; angle < 360; angle += 3)
//		{
//			float angleinradians = (float)(angle * m_pi / 180.0f);
//			float x1 = cosf(angleinradians);
//			float y1 = sinf(angleinradians);
//			glvertex2f(x0, y0);
//			glvertex2f(x1, y1);
//		}
//		glend();
//
//	}
//
//private:
//};

int main()
{
	std::unique_ptr<core::Application> app = std::make_unique<core::Application>("Game of life", 640, 480);

	//std::shared_ptr<core::Layer> triangle = std::make_shared<RgbTriangle>();
	//app->PushOverlay(triangle);

	Configuration conf;
	Logger logger;
	std::shared_ptr<core::Layer> cellsHighlightLayer = std::make_shared<CellsHighlightLayer>(conf, logger);
	app->PushOverlay(cellsHighlightLayer);
	app->Run();
}
