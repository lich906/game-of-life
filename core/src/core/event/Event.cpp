#include "corepch.h"

#include "core/event/Event.h"

namespace core::event
{

std::ostream& operator<<(std::ostream& os, const Event& e)
{
	return os << e.ToString();
}

std::string Event::ToString() const
{
	return GetName();
}

inline bool Event::IsInCategory(EventCategory category)
{
	return GetCategoryFlags() & category;
}

} // namespace core::event
