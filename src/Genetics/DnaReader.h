#pragma once

#include "Dna.h"
#include "DnaReadResult.h"
class Entity;

class DnaReader
{
public:

	DnaReader(const Dna & target);

	DnaReadResult read() const;
	
	DnaReadResult read(size_t start, size_t end) const;


private:

	inline bool can_read(size_t elements) const { return (m_read_point + elements) <= m_target.get_data_size(); }

	template <typename T>
	inline T read_value() const
	{
		void* p = (void*)(&(m_target.get_data()[0]) + m_read_point);
		m_read_point += sizeof(T);
		return *((T*)p);
	}


private:

	const Dna & m_target;
	mutable size_t m_read_point;

};