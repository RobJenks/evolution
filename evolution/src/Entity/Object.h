#pragma once

#include <string>
#include <memory>
#include <variant>
#include "Component.h"
#include "../Util/Result.h"
class DnaReader;


namespace Components
{

	class Object : public Component
	{
	public:

		virtual auto write_dna(DnaWriter& writer) const -> void;
		virtual auto read_dna(const DnaReader& reader)->Result<std::monostate, std::string>;

		auto equals(const Object& other) const -> bool;
	};

}