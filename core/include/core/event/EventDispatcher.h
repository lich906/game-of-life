#pragma once

#include "corepch.h"

#include "Event.h"

namespace core::event
{

class EventDispatcher
{
public:
	EventDispatcher(Event& event)
		: m_event(event)
	{
	}

	// F will be deduced by the compiler
	template <typename T, typename F>
	bool Dispatch(const F& func)
	{
		if (m_event.GetEventType() == T::GetStaticType())
		{
			m_event.handled = func(static_cast<T&>(m_event));
			return true;
		}
		return false;
	}

private:
	Event& m_event;
};

} // namespace core::event
