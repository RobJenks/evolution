#include "ObjectBox.h"
#include "../Genetics/DnaWriter.h"

namespace Components
{

	auto ObjectBox::write_dna(DnaWriter& writer) const -> void
	{
		Object::write_dna(writer);

		// Object size
		writer.write_value(m_halfextents.get<0>());		// x
		writer.write_value(m_halfextents.get<1>());		// y
		writer.write_value(m_halfextents.get<2>());		// z
	}
}