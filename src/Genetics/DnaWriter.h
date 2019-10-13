#pragma once

#include <memory>
#include "Dna.h"
#include "DnaWriteResult.h"
class Entity;

class DnaWriter
{
public:

	DnaWriter(const Entity & source);

	auto write() -> DnaWriteResult;

	template <typename T>
	inline auto write_value(T value) -> void
	{
		unsigned char* p = (unsigned char*)&value;
		for (size_t i = 0; i < sizeof(T); ++i)
		{
			(*m_dna).push_element(*(p++));
		}
	}


private:

	const Entity &			m_source;
	std::unique_ptr<Dna>	m_dna;

};