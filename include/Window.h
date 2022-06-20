#pragma once
#include <SFML/Graphics.hpp>
#include <mutex>

class Window
{
public:
	using DrawCallback = auto (*)(sf::RenderWindow&)->void;

	Window(unsigned width, unsigned height, const sf::String& title);

	void Create();

	void SetActive(bool active = true);

	operator sf::RenderWindow&();

	unsigned GetWidth() const;
	unsigned GetHeight() const;

	bool IsOpen() const;

	void SetDrawCallback(DrawCallback drawCallback, bool clearWindowBeforeDraw = false);

	void SetClearWindowBeforeDraw(bool value);

	void Render();

private:
	bool m_clearWindowBeforeDraw;
	DrawCallback m_drawCallback;

	const unsigned m_width;
	const unsigned m_height;
	sf::String m_title;

	sf::RenderWindow m_window;
};
