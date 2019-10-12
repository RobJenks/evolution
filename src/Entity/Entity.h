#pragma once

#include <memory>
class Dna;

class Entity
{
public:

	Entity();

	std::unique_ptr<Dna> write_dna() const;

private:


};