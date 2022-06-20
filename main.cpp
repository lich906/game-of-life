#include "include/DelimitersDrawer.h"
#include <iostream>

int main()
{
	Window window(800, 600, "Game of life. But not really yet.");
	EventHandler eventHandler;
	DelimitersDrawer delimitersDrawer(window.GetWidth(), window.GetHeight());

	window.Create();
	window.SetActive();

	window.SetDrawCallback(delimitersDrawer.GetDrawCallback());

	char tick = 0;
	while (delimitersDrawer.ProcessEvent(eventHandler.HandleEvents(window)))
	{
		if (tick == RENDER_FREQ)
		{
			window.Render();
			tick = 0;
		}

		sf::sleep(sf::milliseconds(1));
		++tick;
	}

	return 0;
}
