#include "Entity.h"
#include "Component.h"
#include "../Genetics/DnaWriter.h"


Entity::Entity()
{
}

auto Entity::add_component(std::unique_ptr<Components::Component> && comp) -> Components::ComponentId
{
	auto ix = m_comp.size();
	m_comp.emplace_back(std::move(comp));

	return ix;
}

auto Entity::write_dna() const -> DnaWriteResult
{
	return std::move(DnaWriter(*this).write());
}


Entity::~Entity()
{
}