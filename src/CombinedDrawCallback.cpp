#include "CombinedDrawCallback.h"

CombinedDrawCallback::CombinedDrawCallback()
{
}

CombinedDrawCallback::CombinedDrawCallback(std::vector<IDrawer*> drawers)
{
	CombineDrawersCallbacks(drawers);
}

void CombinedDrawCallback::CombineDrawersCallbacks(std::vector<IDrawer*> drawers)
{
	m_callbacks.clear();

	for (const auto& drawer : drawers)
	{
		m_callbacks.push_back(drawer->GetDrawCallback());
	}
}

CombinedDrawCallback& CombinedDrawCallback::Combine(Window::DrawCallback callback)
{
	m_callbacks.push_back(callback);

	return *this;
}

Window::DrawCallback CombinedDrawCallback::Get() const
{
	return CombinedCallback;
}

void CombinedDrawCallback::CombinedCallback(sf::RenderWindow& rw)
{
	for (Window::DrawCallback callback : m_callbacks)
	{
		callback(rw);
	}
}