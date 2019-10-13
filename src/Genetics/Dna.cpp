#include "Dna.h"
#include "DnaReader.h"
#include "../Entity/Entity.h"


auto Dna::get_data() -> Data&
{
	return m_data;
}

auto Dna::get_data() const -> const Data&
{
	return m_data;
}

auto Dna::read() const -> std::unique_ptr<Entity>
{
	return std::move(DnaReader(*this)).read().get();
}