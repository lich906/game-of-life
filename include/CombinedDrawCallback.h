#include "DelimitersDrawer.h"
#include "CellsDrawer.h"

class CombinedDrawCallback
{
public:
	CombinedDrawCallback();

	CombinedDrawCallback(std::vector<IDrawer*> drawers);

	void CombineDrawersCallbacks(std::vector<IDrawer*> drawers);

	CombinedDrawCallback& Combine(Window::DrawCallback callback);

	Window::DrawCallback Get() const;

private:
	static inline std::vector<Window::DrawCallback> m_callbacks;

	static void CombinedCallback(sf::RenderWindow& rw);
};