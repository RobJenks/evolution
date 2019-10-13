#include "Entity.h"
#include "Component.h"
#include "../Genetics/DnaWriter.h"


Entity::Entity()
{
}


auto Entity::write_dna() const -> DnaWriteResult
{
	return std::move(DnaWriter(*this).write());
}


Entity::~Entity()
{
}