#pragma once

#include <variant>

template <typename T, typename E>
class Result
{
public:

	static auto Ok(T value) -> Result<T, E>;
	static auto Err(E err) -> Result<T, E>;

	inline auto is_ok() const -> bool { return m_is_ok; }
	inline auto is_err() const -> bool { return !is_ok(); }

	inline auto get() -> T { return std::get<0>(std::move(m_value)); }
	inline auto get_err() -> E { return std::get<1>(m_value); }

	Result();
	Result(const Result<T, E>& other);
	Result(Result<T, E>&& other) noexcept;

	auto operator=(const Result <T, E> & other) -> Result<T, E>&;
	auto operator=(Result <T, E> && other) noexcept -> Result<T, E>&;

	~Result();

private:

	bool				m_is_ok;
	std::variant<T, E>	m_value;
};

template <typename T, typename E>
auto Result<T, E>::Ok(T value) -> Result<T, E>
{
	Result<T, E> result;
	result.m_is_ok = true;
	result.m_value = std::move(value);

	return result;
}

template <typename T, typename E>
auto Result<T, E>::Err(E err) -> Result<T, E>
{
	Result<T, E> result;
	result.m_is_ok = false;
	result.m_value = std::move(err);

	return result;
}

template <typename T, typename E>
Result<T, E>::Result()
{ 
}

template <typename T, typename E>
Result<T, E>::Result(const Result<T, E> & other)
	:
	m_is_ok(other.m_is_ok),
	m_value(other.m_value)
{
}

template <typename T, typename E>
Result<T, E>::Result(Result<T, E> && other) noexcept
	:
	m_is_ok(other.m_is_ok),
	m_value(std::move(other.m_value))
{
}

template <typename T, typename E>
auto Result<T, E>::operator=(const Result<T, E>& other) -> Result<T, E>&
{
	m_is_ok = other.m_is_ok;
	m_value = other.m_value;
}

template <typename T, typename E>
auto Result<T, E>::operator=(Result <T, E>&& other) noexcept -> Result<T, E>&
{
	m_is_ok = other.m_is_ok;
	m_value = std::move(other.m_value);
}

template <typename T, typename E>
Result<T, E>::~Result()
{
}





