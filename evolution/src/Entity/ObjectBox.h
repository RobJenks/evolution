#include <string>
#include <memory>
#include <variant>
#include "Object.h"
#include "../Util/Vec.h"
#include "../Util/Result.h"
#include "../Genetics/Token.h"
class DnaReader;

#pragma once

namespace Components
{

	class ObjectBox : public Object
	{
	public:

		inline auto get_half_extents() const -> Vec3 { return m_halfextents; }
		inline auto set_half_extents(Vec3 half_extents) -> void { m_halfextents = half_extents; }

		virtual auto write_dna(DnaWriter& writer) const -> void;
		virtual auto read_dna(const DnaReader & reader) -> Result<std::monostate, std::string>;

		inline virtual auto dna_marker() const->Token::Value { return Token::Value::ObjectBox; }

		virtual auto operator==(const Component & other) const -> bool;
		auto equals(const ObjectBox& other) const -> bool;

	private:

		Vec3 m_halfextents;

	};


}