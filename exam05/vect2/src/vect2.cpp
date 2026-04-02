#include "vect2.hpp"

vect2::vect2() : _x(0), _y(0) {}

vect2::vect2(int x, int y) : _x(x), _y(y) {}

vect2::vect2(const vect2 &other) : _x(other._x), _y(other._y) {}

vect2 &vect2::operator=(const vect2 &other)
{
	if (this != &other)
	{
		_x = other._x;
		_y = other._y;
	}
	return (*this);
}

vect2::~vect2() {}

int	&vect2::operator[](int index)
{
	if (index == 0)
		return (_x);
	return (_y);
}

const int	&vect2::operator[](int index) const
{
	if (index == 0)
		return (_x);
	return (_y);
}

std::ostream &operator<<(std::ostream &os, const vect2 &other)
{
	os << "{" << other[0] << ", " << other[1] << "}";
	return (os);
}

vect2 &vect2::operator+=(const vect2 &other)
{
	_x += other._x;
	_y += other._y;
	return (*this);
}
		
vect2 &vect2::operator-=(const vect2 &other)
{
	_x -= other._x;
	_y -= other._y;
	return (*this);
}
	
vect2 &vect2::operator*=(int scalar)
{
	_x *= scalar;
	_y *= scalar;
	return (*this);
}

vect2	operator+(const vect2 &a, const vect2 &b)
{
	vect2	result(a);
	result += b;
	return (result);
}

vect2	operator-(const vect2 &a, const vect2 &b)
{
	vect2	result(a);
	result -= b;
	return (result);
}

vect2	operator*(const vect2 &other, int scalar)
{
	vect2	result(other);
	result *= scalar;
	return (result);
}

vect2	operator*(int scalar, const vect2 &other)
{
	return (other * scalar);
}

vect2	&vect2::operator++(void)
{
	_x++;
	_y++;
	return (*this);
}

vect2	vect2::operator++(int)
{
	vect2	result(*this);
	_x++;
	_y++;
	return (result);
}

vect2	vect2::operator--(int)
{
	vect2	result(*this);
	_x--;
	_y--;
	return (result);
}

vect2	&vect2::operator--(void)
{
	_x--;
	_y--;
	return (*this);
}

vect2 vect2::operator-(void) const
{
	return (vect2(-_x, -_y));
}

bool vect2::operator==(const vect2 &other) const
{
	return (_x == other._x && _y == other._y);
}

bool vect2::operator!=(const vect2 &other) const
{
	return (!(*this == other));
}
