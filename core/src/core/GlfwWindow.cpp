#include "corepch.h"

#include "core/GlfwWindow.h"
#include "core/event/ApplicationEvent.h"
#include "core/event/MouseEvent.h"
#include "core/event/KeyEvent.h"

namespace core
{

GlfwWindow::GlfwWindow(const WindowProps& props)
{
	Init(props);
}

GlfwWindow::~GlfwWindow()
{
	Shutdown();
}

void GlfwWindow::OnUpdate()
{
	glfwPollEvents();
	glfwSwapBuffers(m_window);
}

uint32_t GlfwWindow::GetWidth() const
{
	return m_data.width;
}

uint32_t GlfwWindow::GetHeight() const
{
	return m_data.height;
}

IWindow::Connection GlfwWindow::ListenEvents(const EventSlot& slot)
{
	return m_data.eventSignal.connect(slot);
}

void GlfwWindow::SetVSync(bool enabled)
{
	if (enabled)
		glfwSwapInterval(1);
	else
		glfwSwapInterval(0);

	m_data.vSync = enabled;
}

bool GlfwWindow::IsVSync() const
{
	return m_data.vSync;
}

void* GlfwWindow::GetNativeWindow() const
{
	return m_window;
}

static bool s_GLFWInitialized = false;

static void GLFWErrorCallback(int error, const char* description)
{
	printf("GLFW Error (%d): %s\n", error, description);
}

void GlfwWindow::Init(const WindowProps& props)
{
	m_data.title = props.title;
	m_data.width = props.width;
	m_data.height = props.height;

	if (!s_GLFWInitialized)
	{
		if (!glfwInit())
			throw std::runtime_error("Failed to initialize GLFW.");
		glfwSetErrorCallback(GLFWErrorCallback);
		s_GLFWInitialized = true;
	}

	m_window = glfwCreateWindow((int)props.width, (int)props.height, m_data.title.c_str(), nullptr, nullptr);

	if (m_window == NULL)
		throw std::runtime_error("Failed to create GLFW window.");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Setup OpenGL core profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Enable multisampling
	glfwWindowHint(GLFW_SAMPLES, 4);

	glfwMakeContextCurrent(m_window);
	gladLoadGL();

	glfwSetWindowUserPointer(m_window, &m_data);
	SetVSync(true);

	// Set GLFW callbacks
	glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height) {
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
		data.width = width;
		data.height = height;

		event::WindowResizeEvent event(width, height);
		data.eventSignal(event);
	});

	glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window) {
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
		event::WindowCloseEvent event;
		data.eventSignal(event);
	});

	glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

		switch (action)
		{
		case GLFW_PRESS: {
			event::KeyPressedEvent event(key, 0);
			data.eventSignal(event);
			break;
		}
		case GLFW_RELEASE: {
			event::KeyReleasedEvent event(key);
			data.eventSignal(event);
			break;
		}
		case GLFW_REPEAT: {
			event::KeyPressedEvent event(key, 1);
			data.eventSignal(event);
			break;
		}
		}
	});

	glfwSetCharCallback(m_window, [](GLFWwindow* window, uint32_t keycode) {
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

		event::KeyTypedEvent event(keycode);
		data.eventSignal(event);
	});

	glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods) {
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

		switch (action)
		{
		case GLFW_PRESS: {
			event::MouseButtonPressedEvent event(button);
			data.eventSignal(event);
			break;
		}
		case GLFW_RELEASE: {
			event::MouseButtonReleasedEvent event(button);
			data.eventSignal(event);
			break;
		}
		}
	});

	glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xOffset, double yOffset) {
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

		event::MouseScrolledEvent event((float)xOffset, (float)yOffset);
		data.eventSignal(event);
	});

	glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xPos, double yPos) {
		WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

		event::MouseMovedEvent event((float)xPos, (float)yPos);
		data.eventSignal(event);
	});
}

void GlfwWindow::Shutdown()
{
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

} // namespace core
