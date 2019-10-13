#include "Object.h"
#include "../Util/Vec.h"

#pragma once

namespace Components
{

	class ObjectBox : public Object
	{
	public:

		inline auto get_half_extents() const -> Vec3 { return m_halfextents; }
		inline auto set_half_extents(Vec3 half_extents) -> void { m_halfextents = half_extents; }

		virtual auto write_dna(DnaWriter& writer) const -> void;

		inline virtual auto dna_marker() const->Token::Value { return Token::Value::ObjectBox; }


	private:

		Vec3 m_halfextents;

	};


}