#include "DelimitersDrawer.h"
#include "CellsDrawer.h"

struct CombinedDrawCallback
{
	CombinedDrawCallback& Combine(Window::DrawCallback callback)
	{
		callbacks.push_back(callback);

		return *this;
	}

	Window::DrawCallback Get()
	{
		return CombinedCallback;
	}

private:
	static void CombinedCallback(sf::RenderWindow& rw)
	{
		for (Window::DrawCallback callback : callbacks)
		{
			callback(rw);
		}
	}

	static inline std::vector<Window::DrawCallback> callbacks;
};