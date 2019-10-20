#include "ObjectBox.h"
#include "../Genetics/DnaWriter.h"
#include "../Genetics/DnaReader.h"

namespace Components
{

	auto ObjectBox::write_dna(DnaWriter& writer) const -> void
	{
		Object::write_dna(writer);

		// Object size
		writer.write_value(m_halfextents);
	}

	auto ObjectBox::read_dna(const DnaReader& reader) -> Result<std::monostate, std::string>
	{
		auto result = Object::read_dna(reader);
		if (result.is_err()) return result;

		// Check sufficient data remaining
		if (!reader.can_read_into(m_halfextents))
			return Result<std::monostate, std::string>::Err("Cannot read object; insufficient remaining data");

		reader.read_into(m_halfextents);

		return Result<std::monostate, std::string>::Ok({});
	}

	auto ObjectBox::operator==(const Component & other) const -> bool
	{
		if (dna_marker() != other.dna_marker()) return false;
		const auto& comp = dynamic_cast<const ObjectBox&>(other);

		return equals(comp);
	}

	auto ObjectBox::equals(const ObjectBox& other) const -> bool
	{
		return (
			Object::equals(other) &&

			m_halfextents == other.m_halfextents
		);
	}
}





