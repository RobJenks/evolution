#include "Entity.h"
#include "../Genetics/Dna.h"
#include "../Genetics/DnaWriter.h"

Entity::Entity()
{

}

std::unique_ptr<Dna> Entity::write_dna() const
{
	return DnaWriter(*this).write();
}
