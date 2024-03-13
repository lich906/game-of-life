#include "corepch.h"

#include "core/Input.h"
#include "core/Application.h"

namespace core
{

	bool Input::IsKeyDown(KeyCode keycode)
	{
		GetWindowHandle();
		int state = glfwGetKey(m_windowHandle, (int)keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Input::IsMouseButtonDown(MouseButton button)
	{
		GetWindowHandle();
		int state = glfwGetMouseButton(m_windowHandle, (int)button);
		return state == GLFW_PRESS;
	}

	std::pair<float, float> Input::GetMousePosition()
	{
		GetWindowHandle();
		double x, y;
		glfwGetCursorPos(m_windowHandle, &x, &y);
		return { (float)x, (float)y };
	}

	void Input::SetCursorMode(CursorMode mode)
	{
		GetWindowHandle();
		glfwSetInputMode(m_windowHandle, GLFW_CURSOR, GLFW_CURSOR_NORMAL + (int)mode);
	}

	void Input::GetWindowHandle()
	{
		if (!m_windowHandle)
		{
			m_windowHandle = (GLFWwindow*)Application::Get().GetNativeWindow();
		}
	}

	GLFWwindow* Input::m_windowHandle = nullptr;

}