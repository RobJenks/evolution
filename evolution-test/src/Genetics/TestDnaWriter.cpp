#include "../test.h"

#include <iostream>
#include "Entity/Entity.h"
#include "Entity/ObjectBox.h"
#include "Genetics/Dna.h"

TEST(DnaWriterTests, TestBasicObjectWrite)
{
	auto c1 = std::make_unique<Components::ObjectBox>();
	auto c2 = std::make_unique<Components::ObjectBox>();

	c1.get()->set_half_extents(Vec3({ 1.2f, 3.4f, 5.6f }));
	c2.get()->set_half_extents(Vec3({ 7.8f, 9.0f, 1.2f }));

	Entity e;
	auto id1 = e.add_component(std::move(c1));
	
	c2.get()->set_parent_id(id1);
	auto id2 = e.add_component(std::move(c2));
	
	ASSERT_NE(id1, id2);
	ASSERT_EQ(e.components().size(), 2);

	auto write_result = e.write_dna();
	ASSERT_TRUE(write_result.is_ok());

	auto pdna = write_result.get();
	auto dna = pdna.get();
	
	ASSERT_EQ(dna->get_data(), std::vector<unsigned char>({ 
		170, 170, 170, 170,							// Marker 0xAAAAAAAA
		0, 186, 170, 170,							// Token ObjBox
		255, 255, 255, 255, 255, 255, 255, 255,		// Parent ix: none
		154, 153, 153, 63,							// Half-extent: x
		154, 153, 89, 64,							// Half-extent: y
		51, 51, 179, 64,							// Half-extent: z
		170, 170, 170, 170,							// Marker 0xAAAAAAAA
		0, 186, 170, 170,							// Token ObjBox
		0, 0, 0, 0, 0, 0, 0, 0,						// Parent ix: 0
		154, 153, 249, 64,							// Half-extent: x
		0, 0, 16, 65,								// Half-extent: y
		154, 153, 153, 63							// Half-extent: z
	}));
}



