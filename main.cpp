#include "DelimitersDrawer.h"
#include "CellsDrawer.h"
#include "InitialStateHandler.h"
#include "CombinedDrawCallback.hpp"
#include "CellStateMachine.h"
#include <iostream>

int main()
{
	Window window(WINDOW_WIDTH, WINDOW_HEIGHT, "Game of life. Well... almost.");
	EventHandler eventHandler;
	DelimitersDrawer delimitersDrawer;
	CellsDrawer cellsDrawer;
	InitialStateHandler initStateHandler;

	cellsDrawer.AttachCellsState(initStateHandler.GetInitialState());

	CombinedDrawCallback combinedDrawCallback;
	combinedDrawCallback
		.Combine(delimitersDrawer.GetDrawCallback())
		.Combine(cellsDrawer.GetDrawCallback());

	window.SetDrawCallback(combinedDrawCallback.Get());

	size_t tick = 0;
	auto handledEvents = eventHandler.HandleEvents(window);

	InitialStateHandler::EventProcessingResult result;
	while (
		delimitersDrawer.ProcessEvents(handledEvents) && 
		(result = initStateHandler.ProcessEvents(handledEvents)) != InitialStateHandler::EventProcessingResult::Launch
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

	if (result == InitialStateHandler::EventProcessingResult::Launch)
	{
		tick = 0;
		CellStateMachine stateMachine;

		stateMachine.SetInitialState(initStateHandler.GetInitialState());
		cellsDrawer.AttachCellsState(stateMachine.GetState());

		while (delimitersDrawer.ProcessEvents(handledEvents))
		{
			if (!(tick % RENDER_FREQ))
			{
				window.Render();
			}

			if (tick == STATE_REFRESH_FREQ)
			{
				stateMachine.NextState();
				tick = 0;
			}

			handledEvents = eventHandler.HandleEvents(window);

			sf::sleep(sf::milliseconds(1));
			++tick;
		}
	}

	return 0;
}
