#include "Object.h"

namespace Components
{

	auto Object::write_dna(DnaWriter& writer) const -> void
	{
		Component::write_dna(writer);

		// No addtional data at this level
	}

}