#include "DnaReader.h"

#include <iostream>
#include "Dna.h"
#include "Token.h"
#include "../Entity/Entity.h"

DnaReader::DnaReader(const Dna& target)
	:
	m_target(target),
	m_read_point(0U)
{
}

DnaReadResult DnaReader::read() const
{
	return std::move(read(0U, m_target.get_data_size()));
}

DnaReadResult DnaReader::read(size_t start, size_t end) const
{
	auto entity = std::make_unique<Entity>();
		
	m_read_point = start;
	auto target_size = m_target.get_data_size();

	while (can_read(Token::Size))
	{
		std::cout << "Float: " << read_value<float>() << "\n";
	}

	return DnaReadResult::Ok(std::move(entity));
}