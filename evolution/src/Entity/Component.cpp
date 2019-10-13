#include "Component.h"
#include "../Genetics/DnaWriter.h"

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


	Component::~Component()
	{
	}

}