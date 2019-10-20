#pragma once

#include <vector>
#include <memory>
class Entity;

class Dna
{
public:
	typedef unsigned char Element;
	typedef std::vector<Element> Data;

	Dna();
	Dna(const Dna& other);
	Dna(Dna&& other) noexcept;

	static auto of(Data data) -> std::unique_ptr<Dna>;

	auto operator=(const Dna& other) -> Dna&;
	auto operator=(Dna&& other) noexcept -> Dna&;
	
	auto get_data() -> Data&;
	auto get_data() const -> const Data&;

	inline auto get_data_size() const -> Data::size_type { return m_data.size(); }

	auto read() const -> std::unique_ptr<Entity>;

	inline auto push_element(unsigned char el) -> void { m_data.push_back(el); }

	~Dna();

private:

	auto replace_data(Data data) -> void;

private:
	Data m_data;

};
