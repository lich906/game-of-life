#pragma once
#include "Window.h"

class IDrawer
{
public:
	virtual Window::DrawCallback GetDrawCallback() const = 0;

protected:
	~IDrawer() = default;
};
