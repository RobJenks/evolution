#include "../test.h"
#include "DnaReadWriteFixtures.h"
#include "Util/Vec.h"
#include "Entity/Entity.h"
#include "Entity/ObjectBox.h"
#include "Genetics/Dna.h"

namespace DnaReadWriteFixtures
{
	auto get_basic_dna_data() -> std::vector<unsigned char>
	{
		return std::vector<unsigned char>({
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
		});
	}

	auto get_basic_dna() -> std::unique_ptr<Dna>
	{
		return Dna::of(get_basic_dna_data());
	}

	auto get_basic_entity() -> std::unique_ptr<Entity>
	{
		auto c1 = std::make_unique<Components::ObjectBox>();
		auto c2 = std::make_unique<Components::ObjectBox>();

		c1.get()->set_half_extents(Vec3({ 1.2f, 3.4f, 5.6f }));
		c2.get()->set_half_extents(Vec3({ 7.8f, 9.0f, 1.2f }));

		auto entity = std::make_unique<Entity>();
		auto id1 = (*entity).add_component(std::move(c1));

		c2.get()->set_parent_id(id1);
		auto id2 = (*entity).add_component(std::move(c2));

		assert(id1 != id2);
		assert((*entity).components().size() == 2U);

		return std::move(entity);
	}
}