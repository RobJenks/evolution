#pragma once

#include "Dna.h"
#include "DnaWriteResult.h"
class Entity;

class DnaWriter
{
public:

	DnaWriter(const Entity & source);

	auto write() const-> DnaWriteResult;


private:

	template <typename T>
	inline auto write_value(Dna& dna, T value) const -> void
	{
		unsigned char* p = (unsigned char*)&value;
		for (size_t i = 0; i < sizeof(T); ++i)
		{
			dna.push_element(*(p++));
		}
	}


private:

	const Entity & m_source;


};