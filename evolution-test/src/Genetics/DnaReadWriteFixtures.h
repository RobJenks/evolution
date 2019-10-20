#pragma once

#include <memory>
#include <vector>
class Entity;
class Dna;

namespace DnaReadWriteFixtures 
{
	auto get_basic_dna_data() -> std::vector<unsigned char>;
	auto get_basic_dna() -> std::unique_ptr<Dna>;
	auto get_basic_entity() -> std::unique_ptr<Entity>;
}