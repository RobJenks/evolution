#pragma once

#include "Dna.h"
#include "DnaReadResult.h"
class Entity;

class DnaReader
{
public:

	DnaReader(const Dna & target);

	auto read() const -> DnaReadResult;
	
	auto read(size_t start, size_t end) const -> DnaReadResult;


private:

	inline auto can_read(size_t elements) const -> bool { return (m_read_point + elements) <= m_target.get_data_size(); }

	template <typename T>
	inline auto read_value() const -> T
	{
		void* p = (void*)(&(m_target.get_data()[0]) + m_read_point);
		m_read_point += sizeof(T);
		return *((T*)p);
	}


private:

	const Dna & m_target;
	mutable size_t m_read_point;

};