#include "Dna.h"
#include "DnaReader.h"
#include "../Entity/Entity.h"


Dna::Data& Dna::get_data()
{
	return m_data;
}

const Dna::Data& Dna::get_data() const
{
	return m_data;
}

std::unique_ptr<Entity> Dna::read() const
{
	//return std::move(DnaReader(*this).read().take());
	return std::move(DnaReader(*this)).read().get();
}