#ifndef COMMON_HPP
# define COMMON_HPP

# include <algorithm>
# include <iostream>
# include <memory>
# include <vector>

namespace ft
{
	template<class T>
	std::ostream &print_shared_ptr_member(std::ostream &o, const std::shared_ptr<T> &member)
	{
		return (member ? o << *member : o << "(null)");
	}

	template <template <typename...> class C, typename T>
	std::ostream &print_shared_ptr_container(std::ostream &o, const C<std::shared_ptr<T>> &container)
	{
		const size_t container_size = container.size();
		size_t i = 0;
		o << "{ ";
		for (const auto &ptr : container)
		{
			if (ptr)
				o << *ptr;
			else
				o << "(null)";
			if (i != container_size - 1)
				o << ", ";
			i++;
		}
		o << " }";
		return (o);
	}

	template<class T, class Alloc, class U = T>
	constexpr typename std::vector<T, Alloc>::size_type erase(std::vector<T, Alloc> &c, const U &value)
	{
		const auto it = std::remove(c.begin(), c.end(), value);
		const auto r = c.end() - it;
		c.erase(it, c.end());
		return (r);
	}
}

#endif
