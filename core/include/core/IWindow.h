#pragma once

#include "corepch.h"

#include "core/event/Event.h"

namespace core
{

struct WindowProps
{
	std::string title;
	uint32_t width;
	uint32_t height;

	WindowProps(const std::string& title = "Untitled",
		uint32_t width = 1280,
		uint32_t height = 720)
		: title(title)
		, width(width)
		, height(height)
	{
	}
};

class IWindow
{
public:
	using EventSignal = sigslot::signal<event::Event&>;
	using EventSlot = std::function<void(event::Event&)>;
	using Connection = sigslot::connection;

	virtual ~IWindow() = default;

	virtual void OnUpdate() = 0;

	virtual uint32_t GetWidth() const = 0;
	virtual uint32_t GetHeight() const = 0;

	virtual Connection ListenEvents(const EventSlot& slot) = 0;
	virtual void SetVSync(bool enabled) = 0;
	virtual bool IsVSync() const = 0;

	virtual void* GetNativeWindow() const = 0;
};

} // namespace core
