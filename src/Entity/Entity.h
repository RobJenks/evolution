#pragma once

#include <memory>
#include "../Genetics/DnaWriteResult.h"

class Entity
{
public:

	Entity();

	auto write_dna() const -> DnaWriteResult;

private:


};