#pragma once

#include "corepch.h"

#include "IWindow.h"

namespace core
{

class GlfwWindow : public IWindow
{
public:
	GlfwWindow(const WindowProps& props);
	virtual ~GlfwWindow();

	// Inherited via IGlfwWindow
	virtual void OnUpdate() override;
	virtual uint32_t GetWidth() const override;
	virtual uint32_t GetHeight() const override;
	virtual Connection ListenEvents(const EventSlot& slot) override;
	virtual void SetVSync(bool enabled) override;
	virtual bool IsVSync() const override;
	virtual void* GetNativeWindow() const override;

private:
	virtual void Init(const WindowProps& props);
	virtual void Shutdown();

	GLFWwindow* m_window;

	struct WindowData
	{
		std::string title;
		uint32_t width{}, height{};
		bool vSync = false;
		EventSignal eventSignal;
	} m_data;
};

} // namespace core
