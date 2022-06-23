#include "DelimitersDrawer.h"
#include "CellsDrawer.h"
#include "InitialStateHandler.h"
#include "CombinedDrawCallback.hpp"
#include <iostream>

int main()
{
	Window window(WINDOW_WIDTH, WINDOW_HEIGHT, "Game of life. Well... almost.");
	EventHandler eventHandler;
	DelimitersDrawer delimitersDrawer;
	CellsDrawer cellsDrawer;
	InitialStateHandler initStateHandler;

	window.Create();
	window.SetActive();

	cellsDrawer.AttachCellsState(initStateHandler.GetInitialState());

	CombinedDrawCallback combinedDrawCallback;
	combinedDrawCallback
		.Combine(delimitersDrawer.GetDrawCallback())
		.Combine(cellsDrawer.GetDrawCallback());

	window.SetDrawCallback(combinedDrawCallback.Get());

	char tick = 0;
	auto handledEvents = eventHandler.HandleEvents(window);
	while (
		delimitersDrawer.ProcessEvents(handledEvents)
		&& initStateHandler.ProcessEvents(handledEvents)
	)
	{
		if (tick == RENDER_FREQ)
		{
			window.Render();
			tick = 0;
		}

		handledEvents = eventHandler.HandleEvents(window);

		sf::sleep(sf::milliseconds(1));
		++tick;
	}

	return 0;
}
