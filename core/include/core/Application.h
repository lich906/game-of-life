#pragma once

#include "core/IWindow.h"
#include "core/LayerStack.h"
#include "core/event/Event.h"
#include "core/event/ApplicationEvent.h"
#include "core/Timestep.h"
#include "core/utils/ScopedConnections.h"

namespace core
{

class Application
{
public:
	Application(const std::string& name = "Untitled", uint32_t width = 1280, uint32_t height = 720);
	virtual ~Application() = default;

	void Run();

	void OnEvent(event::Event& e);

	void PushLayer(const std::shared_ptr<Layer>& layer);
	void PushOverlay(const std::shared_ptr<Layer>& layer);

	inline IWindow& GetWindow() { return *m_window; }
	inline void* GetNativeWindow() { return m_window->GetNativeWindow(); }

	inline static Application& Get() { return *s_instance; }

private:
	bool OnWindowClose(event::WindowCloseEvent& e);

	std::unique_ptr<IWindow> m_window;

	bool m_running = true;
	LayerStack m_layerStack;
	float m_lastFrameTime = 0.0f;
	utils::ScopedConnections m_conns;

	static Application* s_instance;
};

} // namespace core
