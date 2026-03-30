#include "set.hpp"

set::set() : _bag(0) {}

set::set(searchable_bag &bag) : _bag(&bag) {}

set::set(const set &other) : _bag(other._bag) {}

set &set::operator=(const set &other)
{
	_bag = other._bag;
	return (*this);
}

set::~set() {}

void	set::insert(int n)
{
	if (!_bag->has(n))
		_bag->insert(n);
}

void	set::insert(int *arr, int size)
{
	for (int i = 0; i < size; i++)
		this->insert(arr[i]);
}

void	set::print() const
{
	_bag->print();
}

void	set::clear()
{
	_bag->clear();
}

bool	set::has(int n) const
{
	return (_bag->has(n));
}

searchable_bag	&set::get_bag() const
{
	return (*_bag);
}
