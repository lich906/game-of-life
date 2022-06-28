#include "DelimitersDrawer.h"
#include "CellsDrawer.h"
#include "InitialStateHandler.h"
#include "CombinedDrawCallback.hpp"
#include "CellStateMachine.h"
#include "CommonEventProcessor.h"
#include "Config.h"
#include <iostream>

enum class Stage
{
	Initialization,
	Game
};

int main()
{
	try
	{
		Config::ReadFromFile("config.txt");
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	Window window(Config::GetWindowWidth(), Config::GetWindowHeight(), "Game of life. v0.3");
	DelimitersDrawer delimitersDrawer;
	CellsDrawer cellsDrawer;
	InitialStateHandler initStateHandler;
	CellStateMachine stateMachine(Config::GetWindowWidth() / Config::GetCellSize(), Config::GetWindowHeight() / Config::GetCellSize());

	cellsDrawer.AttachCellsState(initStateHandler.GetInitialState());

	CombinedDrawCallback combinedDrawCallback;
	combinedDrawCallback
		.Combine(delimitersDrawer.GetDrawCallback())
		.Combine(cellsDrawer.GetDrawCallback());

	window.SetDrawCallback(combinedDrawCallback.Get());

	size_t tick = 0;

	auto events = EventCollector::CollectEvents(window);

	EventResFlag::Flag eventResFlags = 
		delimitersDrawer.ProcessEvents(events) |
		initStateHandler.ProcessEvents(events) |
		CommonEventProcessor::ProcessEvents(events);

	Stage stage = Stage::Initialization;

	while (!(eventResFlags & EventResFlag::Exit))
	{
		if (!(tick % Config::GetFrameRefreshTime()))
		{
			window.Render();
		}

		if (!(tick % Config::GetStateRefreshTime()) && stage == Stage::Game)
		{
			stateMachine.NextState();
		}

		if ((eventResFlags & EventResFlag::LaunchGame) && stage == Stage::Initialization)
		{
			stateMachine.SetInitialState(initStateHandler.GetInitialState());
			cellsDrawer.AttachCellsState(stateMachine.GetState());

			stage = Stage::Game;
		}

		if (eventResFlags & EventResFlag::ResetGame)
		{
			initStateHandler.ResetState();
			cellsDrawer.AttachCellsState(initStateHandler.GetInitialState());
			window.Clear();

			stage = Stage::Initialization;
		}

		events = EventCollector::CollectEvents(window);

		if (stage == Stage::Initialization)
		{
			eventResFlags = 
				delimitersDrawer.ProcessEvents(events) |
				initStateHandler.ProcessEvents(events);
		}
		else
		{
			eventResFlags = delimitersDrawer.ProcessEvents(events);
		}

		eventResFlags |= CommonEventProcessor::ProcessEvents(events);

		sf::sleep(sf::milliseconds(1));
		++tick;
	}

	return 0;
}
