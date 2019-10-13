#pragma once

#include <memory>
#include <vector>
#include "../Genetics/DnaWriteResult.h"
#include "Component.h"

class Entity
{
public:

	Entity();

	inline auto components() -> std::vector<std::unique_ptr<Components::Component>>& { return m_comp; }
	inline auto components() const -> const std::vector<std::unique_ptr<Components::Component>>& { return m_comp; }

	auto add_component(std::unique_ptr<Components::Component>&& comp) -> Components::ComponentId;

	auto write_dna() const -> DnaWriteResult;

	~Entity();

private:

	std::vector<std::unique_ptr<Components::Component>> m_comp;

};