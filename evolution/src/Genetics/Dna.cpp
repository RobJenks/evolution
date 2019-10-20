#include <memory>
#include "Dna.h"
#include "DnaReader.h"
#include "../Entity/Entity.h"


Dna::Dna()
{
}

auto Dna::of(Data data) -> std::unique_ptr<Dna>
{
	auto dna = std::make_unique<Dna>();
	dna.get()->replace_data(data);

	return dna;
}

auto Dna::get_data() -> Data&
{
	return m_data;
}

auto Dna::get_data() const -> const Data&
{
	return m_data;
}

auto Dna::replace_data(Data data) -> void
{
	m_data = data;
}

auto Dna::read() const -> std::unique_ptr<Entity>
{
	return std::move(DnaReader(*this)).read().get();
}

Dna::Dna(const Dna& other)
	:
	m_data(other.m_data)
{
}
Dna::Dna(Dna&& other) noexcept
	:
	m_data(std::move(other.m_data))
{
}

auto Dna::operator=(const Dna& other)->Dna&
{
	m_data = other.m_data;
	
	return *this;
}
auto Dna::operator=(Dna&& other) noexcept -> Dna&
{
	m_data = std::move(other.m_data);

	return *this;
}

Dna::~Dna()
{
}
