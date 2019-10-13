#include <algorithm>
#include "DnaWriter.h"
#include "../Entity/Entity.h"
#include "../Entity/Component.h"

DnaWriter::DnaWriter(const Entity& source)
	:
	m_source(source),
	m_dna(std::make_unique<Dna>())
{
}

auto DnaWriter::write() -> DnaWriteResult
{
	const auto & comp = m_source.components();
	std::for_each(comp.cbegin(), comp.cend(), [this](const auto & c) { c.get()->write_dna(*this); });

	return DnaWriteResult::Ok(std::move(m_dna));
}

