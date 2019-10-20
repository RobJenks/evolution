#include "DnaReader.h"

#include <iostream>
#include "Dna.h"
#include "Token.h"
#include "../Entity/Entity.h"
#include "../Entity/ObjectBox.h"

#define ENSURE_CAN_READ(n) { if (!can_read(n)) { return DnaReadResult::Err("Cannot read " + std::to_string(n) + " bytes; current read point at " + std::to_string(m_read_point)); } }
#define ENSURE_CAN_READ_TYPE(_typ) ENSURE_CAN_READ(sizeof(_typ));

DnaReader::DnaReader(const Dna& target)
	:
	m_target(target),
	m_read_point(0U)
{
}

auto DnaReader::read() const -> DnaReadResult
{
	return std::move(read(0U, m_target.get_data_size()));
}

auto DnaReader::read(size_t start, size_t end) const -> DnaReadResult
{
	auto entity = std::make_unique<Entity>();
		
	m_read_point = start;
	
	while (can_read(Token::Size))
	{
		// Read and validate prefix marker
		const auto marker_start = m_read_point;
		const auto marker = read_value<Token::Value>();
		if (marker != Token::Value::Marker) {
			return DnaReadResult::Err("Read failed: missing expected marker token at read point " + std::to_string(marker_start));
		}

		// Read and validate component type
		ENSURE_CAN_READ_TYPE(Token::Value)
		switch (auto type = read_value<Token::Value>())
		{
			case Token::Value::ObjectBox: {
				auto comp = std::make_unique<Components::ObjectBox>();
				auto read_result = comp.get()->read_dna(*this);
				if (read_result.is_err()) {
					return DnaReadResult::Err("Failed to read component at read_point " + std::to_string(marker_start) + ": " + read_result.get_err());
				}

				entity.get()->add_component(std::move(comp));
				break;
			}
			default:
				return DnaReadResult::Err("Read failed; unknown token type " + std::to_string(static_cast<Token::Type>(type)));
		}

	}

	return DnaReadResult::Ok(std::move(entity));
}