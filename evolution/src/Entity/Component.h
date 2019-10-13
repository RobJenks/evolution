#pragma once

#include <vector>
#include "ComponentId.h"
#include "../Genetics/Token.h"
class DnaWriter;

namespace Components
{
	class Component
	{
	public:

		Component();

		inline auto get_parent_id() const -> ComponentId { return m_parent; }
		inline auto set_parent_id(ComponentId parent_id) -> void { m_parent = parent_id; }

		inline auto children() -> std::vector<ComponentId>& { return m_children; }
		inline auto children() const -> const std::vector<ComponentId>& { return m_children; }
		
		// Implemented by concrete classes: returns the dna token associated with this class of component
		virtual auto dna_marker() const-> Token::Value = 0;

		virtual auto write_dna(DnaWriter& writer) const -> void;

		~Component();

	protected:
		ComponentId					m_parent;
		std::vector<ComponentId>	m_children;

	};
}