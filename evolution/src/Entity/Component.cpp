#include "Component.h"
#include "../Util/Result.h"
#include "../Genetics/DnaWriter.h"
#include "../Genetics/DnaReader.h"

namespace Components
{

	Component::Component()
		:
		m_parent(NO_ID)
	{
	}

	auto Component::write_dna(DnaWriter& writer) const -> void
	{
		// Token marker
		writer.write_value(Token::Value::Marker);
		writer.write_value(dna_marker());

		// Parent ID
		writer.write_value(m_parent);
	}

	auto Component::read_dna(const DnaReader & reader) -> Result<std::monostate, std::string>
	{
		// Token marker & type are not read; they have already been read in order to invoke this process

		// Parent ID
		if (!reader.can_read_type<ComponentId>()) return Result<std::monostate, std::string>::Err("Cannot read component ID");
		m_parent = reader.read_value<ComponentId>();

		return Result<std::monostate, std::string>::Ok({});
	}

	auto Component::equals(const Component& other) const -> bool
	{
		return (
			dna_marker() == other.dna_marker() &&
			m_parent == other.m_parent
		);
	}

	Component::~Component()
	{
	}

}