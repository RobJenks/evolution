#pragma once

#include "Dna.h"
#include "DnaWriteResult.h"
class Entity;

class DnaWriter
{
public:

	DnaWriter(const Entity & source);

	DnaWriteResult write() const;


private:

	template <typename T>
	inline void write_value(Dna& dna, T value) const
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