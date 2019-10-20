#include "../test.h"

#include <iostream>
#include "DnaReadWriteFixtures.h"
#include "Entity/Entity.h"
#include "Entity/ObjectBox.h"
#include "Genetics/Dna.h"

TEST(DnaWriterTests, TestBasicObjectWrite)
{
	auto entity = DnaReadWriteFixtures::get_basic_entity();
	auto & e = *(entity.get());

	auto write_result = e.write_dna();
	ASSERT_TRUE(write_result.is_ok());

	auto dna = write_result.get();
	
	auto dna_data = (*dna).get_data();
	auto expected_data = DnaReadWriteFixtures::get_basic_dna_data();

	ASSERT_EQ(dna_data, expected_data);
}



