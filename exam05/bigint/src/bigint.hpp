#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <vector>
#include <iostream>
#include <algorithm>

class    bigint
{    
	private:
		std::vector<int>    _value;
	public:
		bigint(void);
		bigint(unsigned int n);
		bigint(const bigint &other);
		bigint &operator=(const bigint &other);
		~bigint(void);

		const std::vector<int>	&getValue(void) const;
	
		bigint operator+(const bigint &other) const;
		bigint &operator+=(const bigint &other);

		// pre increment
		bigint &operator++(void);

		// pos increment
		bigint operator++(int);

		bool operator<(const bigint &other) const;
		bool operator>(const bigint &other) const;
		bool operator>=(const bigint &other) const;
		bool operator<=(const bigint &other) const;
		bool operator==(const bigint &other) const;
		bool operator!=(const bigint &other) const;

		bigint operator<<(const bigint &other) const;
		bigint operator>>(const bigint &other) const;
		bigint &operator<<=(const bigint &other);
		bigint &operator>>=(const bigint &other);
};

std::ostream &operator<<(std::ostream &os, const bigint &other);

#endif
