#include "Window.h"

Window::Window(unsigned width, unsigned height, const sf::String& title)
	: m_width(width)
	, m_height(height)
	, m_title(title)
{
}

void Window::Create()
{
	m_window.create(sf::VideoMode(m_width, m_height), m_title);
}

void Window::SetActive(bool active)
{
	m_window.setActive(active);
}

Window::operator sf::RenderWindow&()
{
	return m_window;
}

unsigned Window::GetWidth() const
{
	return m_width;
}

unsigned Window::GetHeight() const
{
	return m_height;
}

bool Window::IsOpen() const
{
	return m_window.isOpen();
}

void Window::SetDrawCallback(DrawCallback drawCallback, bool clearWindowBeforeDraw)
{
	m_drawCallback = drawCallback;
	m_clearWindowBeforeDraw = clearWindowBeforeDraw;
}

void Window::SetClearWindowBeforeDraw(bool value)
{
	m_clearWindowBeforeDraw = value;
}

void Window::Render()
{
	if (m_clearWindowBeforeDraw)
	{
		m_window.clear();
	}

	m_drawCallback(m_window);

	m_window.display();
}
