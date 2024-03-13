#pragma once

#include "corepch.h"

#include "core/Timestep.h"
#include "core/event/Event.h"

namespace core
{

class Layer
{
public:
	Layer(const std::string& name = "Layer");
	virtual ~Layer() = default;

	virtual void OnAttach() {}
	virtual void OnDetach() {}
	virtual void OnUpdate(Timestep ts) {}
	virtual void OnEvent(event::Event& event) {}

	inline const std::string& GetName() const { return m_debugName; }
protected:
	std::string m_debugName;
};

} // namespace core
