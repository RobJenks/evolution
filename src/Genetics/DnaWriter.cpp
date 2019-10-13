#include "DnaWriter.h"

DnaWriter::DnaWriter(const Entity& source)
	:
	m_source(source)
{
}

DnaWriteResult DnaWriter::write() const
{
	auto d = std::make_unique<Dna>();	

	write_value<float>(*d.get(), 12.34f);
	write_value<float>(*d.get(), 56.78f);

	return DnaWriteResult::Ok(std::move(d));
}

