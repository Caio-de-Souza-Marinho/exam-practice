#ifndef SET_HPP
#define SET_HPP

#include "subject/searchable_bag.hpp"

class	set : public searchable_bag
{
	private:
		searchable_bag	*_bag;

	public:
		set();
		set(searchable_bag &bag);
		set(const set &other);
		set &operator=(const set &other);
		~set();

		void	insert(int); 
		void	insert(int *, int);
		void	print() const; 
		void	clear();
		bool	has(int) const;
		searchable_bag	&get_bag() const;
};

#endif
