#ifndef VECT2_HPP
#define VECT2_HPP

#include <iostream>

class	vect2
{
	private:
		int	_x;
		int	_y;

	public:
		vect2();
		vect2(int x, int y);
		vect2(const vect2 &other);
		vect2 &operator=(const vect2 &other);
		~vect2();

		vect2 &operator+=(const vect2 &other);
		vect2 &operator-=(const vect2 &other);
		vect2 &operator*=(int scalar);

		vect2 &operator++(void);
		vect2 operator++(int);
		vect2 &operator--(void);
		vect2 operator--(int);

		vect2 operator-(void) const;

		int		&operator[](int index);
		const int	&operator[](int index) const;

		bool operator==(const vect2 &other) const;
		bool operator!=(const vect2 &other) const;
};

vect2	operator+(const vect2 &a, const vect2 &b);
vect2	operator-(const vect2 &a, const vect2 &b);
vect2	operator*(const vect2 &other, int scalar);
vect2	operator*(int scalar, const vect2 &other);

std::ostream &operator<<(std::ostream &os, const vect2 &other);

#endif
