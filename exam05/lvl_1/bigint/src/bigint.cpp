#include "bigint.hpp"

bigint::bigint(void)
{
	_value.push_back(0);
}

bigint::bigint(unsigned int n)
{
	if (n == 0)
	{
		_value.push_back(0);
		return ;
	}
	while (n > 0)
	{
		_value.push_back(n % 10);
		n /= 10;
	}
}

bigint::bigint(const bigint &other)
{
	*this = other;
}

bigint &bigint::operator=(const bigint &other)
{
	if (this != &other)
		_value = other._value;
	return (*this);
}

bigint::~bigint(void) {}

const std::vector<int>	&bigint::getValue(void) const
{
	return (_value);
}

std::ostream &operator<<(std::ostream &os, const bigint &other)
{
	std::vector<int>		temp= other.getValue();
	std::vector<int>::iterator	start = temp.begin();
	std::vector<int>::iterator	end = temp.end();

	while (start != end)
	{
		end--;
		os << *end;
	}
	return (os);
}

bigint &bigint::operator+=(const bigint &other)
{
	int	carry = 0;
	size_t	len = std::max(_value.size(), other._value.size());

	for (size_t i = 0; i < len || carry; i++)
	{
		int	sum = carry;
		if (i < _value.size())
			sum += _value[i];
		if (i < other._value.size())
			sum += other._value[i];
		if (i >= _value.size())
			_value.push_back(0);
		_value[i] = sum % 10;
		carry = sum / 10;
	}
	return (*this);
}

bigint bigint::operator+(const bigint &other) const
{
	bigint	result(*this);
	result += other;
	return (result);
}

bigint &bigint::operator++(void)
{
	*this += 1;
	return (*this);
}

bigint bigint::operator++(int)
{
	bigint	temp = *this;
	*this += 1;
	return (temp);
}

bool bigint::operator<(const bigint &other) const
{
	if (this->_value.size() < other._value.size())
		return (true);
	if (this->_value.size() > other._value.size())
		return (false);

	size_t	len = this->_value.size();
	for (size_t i = len; i-- > 0;)
	{
		if (this->_value[i] < other._value[i])
			return (true);
		if (this->_value[i] > other._value[i])
			return (false);
	}
	return (false);
}

bool bigint::operator>(const bigint &other) const
{
	return (other < *this);
}

bool bigint::operator>=(const bigint &other) const
{
	return (!(*this < other));
}

bool bigint::operator<=(const bigint &other) const
{
	return (!(other < *this));
}

bool bigint::operator==(const bigint &other) const
{
	return (!(*this < other) && !(other < *this));
}

bool bigint::operator!=(const bigint &other) const
{
	return (!(*this == other));
}

bigint &bigint::operator<<=(const bigint &other)
{
	size_t	shift = 0;
	size_t	base = 1;
	std::vector<int>	vector = other.getValue();
	for (size_t i = 0; i < vector.size(); i++)
	{
		shift += vector[i] * base;
		base *= 10;
	}
	_value.insert(_value.begin(), shift, 0);
	return (*this);
}

bigint bigint::operator<<(const bigint &other) const
{
	bigint	result(*this);
	result <<= other;
	return (result);
}

bigint &bigint::operator>>=(const bigint &other)
{
	size_t	shift = 0;
	size_t	base = 1;
	std::vector<int>	vector = other.getValue();
	for (size_t i = 0; i < vector.size(); i++)
	{
		shift += vector[i] * base;
		base *= 10;
	}
	if (shift >= _value.size())
	{
		_value.clear();
		_value.push_back(0);
		return (*this);
	}
	_value.erase(_value.begin(), _value.begin() + shift);
	return (*this);
}

bigint bigint::operator>>(const bigint &other) const
{
	bigint	result(*this);
	result >>= other;
	return (result);
}
