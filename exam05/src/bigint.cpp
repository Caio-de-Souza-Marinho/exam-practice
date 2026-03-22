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

bigint::~bigint() {}
