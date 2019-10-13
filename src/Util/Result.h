#pragma once

#include <variant>

template <typename T, typename E>
class Result
{
public:

	static Result<T, E> Ok(T value);
	static Result<T, E> Err(E err);

	inline bool is_ok() const { return m_is_ok; }
	inline bool is_err() const { return !is_ok(); }

	inline T get() { return std::get<0>(std::move(m_value)); }
	//inline T && take() const { return std::move(std::get<0>(std::move(m_value))); }
	inline E get_err() { return std::get<1>(m_value); }

	Result();
	Result(const Result<T, E>& other);
	Result(Result<T, E>&& other);

	Result<T, E>& operator=(const Result <T, E> & other);
	Result<T, E>& operator=(Result <T, E> && other);

	~Result();

private:

	bool				m_is_ok;
	std::variant<T, E>	m_value;
};

template <typename T, typename E>
Result<T, E> Result<T, E>::Ok(T value)
{
	Result<T, E> result;
	result.m_is_ok = true;
	result.m_value = std::move(value);

	return result;
}

template <typename T, typename E>
Result<T, E> Result<T, E>::Err(E err)
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
Result<T, E>::Result(Result<T, E> && other)
	:
	m_is_ok(other.m_is_ok),
	m_value(std::move(other.m_value))
{
}

template <typename T, typename E>
Result<T, E> & Result<T, E>::operator=(const Result<T, E>& other)
{
	m_is_ok = other.m_is_ok;
	m_value = other.m_value;
}

template <typename T, typename E>
Result<T, E> & Result<T, E>::operator=(Result <T, E>&& other)
{
	m_is_ok = other.m_is_ok;
	m_value = std::move(other.m_value);
}

template <typename T, typename E>
Result<T, E>::~Result()
{
}





