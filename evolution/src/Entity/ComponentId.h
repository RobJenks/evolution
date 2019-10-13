#pragma once

#include <limits>

namespace Components
{
	typedef size_t ComponentId;

	static const ComponentId NO_ID = std::numeric_limits<ComponentId>::max();
};