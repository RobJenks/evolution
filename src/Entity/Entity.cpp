#include "Entity.h"
#include "../Genetics/DnaWriter.h"

Entity::Entity()
{

}

DnaWriteResult Entity::write_dna() const
{
	return std::move(DnaWriter(*this).write());
}
