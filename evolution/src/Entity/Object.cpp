#include "Object.h"

namespace Components
{

	auto Object::write_dna(DnaWriter& writer) const -> void
	{
		Component::write_dna(writer);

		// No addtional data at this level
	}

	auto Object::read_dna(const DnaReader& reader) -> Result<std::monostate, std::string>
	{
		auto result = Component::read_dna(reader);
		if (result.is_err()) return result;

		// No additional data at this level
		return Result<std::monostate, std::string>::Ok({});
	}

	auto Object::equals(const Object& other) const -> bool
	{
		// No additional data at this level
		return Component::equals(other);
	}

}