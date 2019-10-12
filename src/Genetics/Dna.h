#pragma once

#include <vector>
#include <memory>
class Entity;

class Dna
{
public:
	typedef unsigned char Element;
	typedef std::vector<Element> Data;

	Data & get_data();
	const Data & get_data() const;

	inline Data::size_type get_data_size() const { return m_data.size(); }

	std::unique_ptr<Entity> read() const;

	inline void push_element(unsigned char el) { m_data.push_back(el); }


private:
	Data m_data;

};
