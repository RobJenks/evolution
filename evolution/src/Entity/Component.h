#pragma once

#include <string>
#include <vector>
#include <variant>
#include "ComponentId.h"
#include "../Util/Result.h"
#include "../Genetics/Token.h"
class DnaReader;
class DnaWriter;

namespace Components
{
	class Component
	{
	public:

		Component();

		inline auto get_parent_id() const -> ComponentId { return m_parent; }
		inline auto set_parent_id(ComponentId parent_id) -> void { m_parent = parent_id; }

		// Not part of serialised dna string; for convenience
		inline auto children() -> std::vector<ComponentId>& { return m_children; }
		inline auto children() const -> const std::vector<ComponentId>& { return m_children; }
		
		// Implemented by concrete classes: returns the dna token associated with this class of component
		virtual auto dna_marker() const-> Token::Value = 0;

		// Extended by all stateful subclasses
		virtual auto write_dna(DnaWriter & writer) const -> void;
		virtual auto read_dna(const DnaReader & reader)->Result<std::monostate, std::string>;

		// Operator== is implemented by all concrete subclasses.  "equals" is implemented by all subclasses
		virtual auto operator==(const Component& other) const -> bool = 0;
		auto equals(const Component& other) const -> bool;

		~Component();

	protected:
		ComponentId					m_parent;
		std::vector<ComponentId>	m_children;

	};
}