#pragma once

#include <array>


template <unsigned int N, typename T>
class Vec
{
public:

	Vec();
	Vec(std::array<T, N>&& data);

	Vec(const Vec<N, T>& other);
	Vec(Vec<N, T>&& other) noexcept;

	auto operator=(const Vec<N, T> & other) -> Vec<N, T>&;
	auto operator=(Vec<N, T> && other) noexcept -> Vec<N, T>&;

	template <unsigned int Ix>
	inline auto get() const -> T { return std::get<Ix>(m_data); }

	inline auto get(size_t ix) const -> T { return m_data[ix]; }
	inline auto set(size_t ix, T&& val) -> void { m_data[ix] = val; }

private:

	std::array<T, N> m_data;

};

typedef Vec<2U, float> Vec2;
typedef Vec<3U, float> Vec3;
typedef Vec<4U, float> Vec4;

typedef Vec<2U, int> IntVec2;
typedef Vec<3U, int> IntVec3;
typedef Vec<4U, int> IntVec4;


template<unsigned int N, typename T>
Vec<N, T>::Vec()
	:
	m_data({})
{
}

template<unsigned int N, typename T>
Vec<N, T>::Vec(std::array<T, N>&& data)
	:
	m_data(data)
{
}

template<unsigned int N, typename T>
Vec<N, T>::Vec(const Vec<N, T>& other)
	:
	m_data(other.m_data)
{
}

template<unsigned int N, typename T>
Vec<N, T>::Vec(Vec<N, T>&& other) noexcept
	:
	m_data(std::move(other.m_data))
{
}


template<unsigned int N, typename T>
auto Vec<N, T>::operator=(const Vec<N, T>& other) -> Vec<N, T>&
{
	m_data = other.m_data;

	return *this;
}

template<unsigned int N, typename T>
auto Vec<N, T>::operator=(Vec<N, T>&& other) noexcept -> Vec<N, T>&
{
	m_data = std::move(other.m_data);

	return *this;
}
