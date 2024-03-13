#pragma once

#include "corepch.h"

#include "KeyCodes.h"

namespace core
{

class Input
{
public:
	static bool IsKeyDown(KeyCode keycode);
	static bool IsMouseButtonDown(MouseButton button);
	static std::pair<float, float> GetMousePosition();
	static void SetCursorMode(CursorMode mode);

private:
	static void GetWindowHandle();

	static GLFWwindow* m_windowHandle;
};

}
