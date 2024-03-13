#include "corepch.h"

#include "core/utils/ScopedConnections.h"

namespace core::utils
{

ScopedConnections::ScopedConnections()
{
}

ScopedConnections::ScopedConnections(std::vector<ScopedConnection>&& connectionsVect)
	: m_connections(std::forward<std::vector<ScopedConnection>>(connectionsVect))
{
}

ScopedConnections& ScopedConnections::operator+=(ScopedConnection&& connection)
{
	m_connections.emplace_back(std::move(connection));
	return *this;
}

} // namespace core::utils
