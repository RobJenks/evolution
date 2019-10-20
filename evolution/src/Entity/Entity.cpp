#include <algorithm>
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

auto Entity::operator==(const Entity& other) const -> bool
{
	auto n_comp = components().size();
	if (other.components().size() != n_comp) return false;

	for (size_t i = 0U; i < n_comp; ++i)
	{
		const auto & c = *(components()[i]);
		const auto & c_other = *(other.components()[i]);

		if (!(c == c_other)) return false;
	}

	return true;
}

Entity::~Entity()
{
}