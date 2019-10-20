#include "../test.h"

#include "DnaReadWriteFixtures.h"
#include "Genetics/Dna.h"
#include "Genetics/DnaReader.h"
#include "Entity/Entity.h"

TEST(DnaReaderTests, TestBasicObjectRead)
{
	auto dna = DnaReadWriteFixtures::get_basic_dna();

	auto read_result = DnaReader(*dna.get()).read();
	ASSERT_TRUE(read_result.is_ok());

	auto entity = read_result.get();
	auto expected = DnaReadWriteFixtures::get_basic_entity();

	ASSERT_EQ((*entity), (*expected));
}

