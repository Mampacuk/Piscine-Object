#ifndef PACKAGEREDUCTIONDISCOUNT_HPP
# define PACKAGEREDUCTIONDISCOUNT_HPP

# include "command.hpp"

class PackageReductionDiscount : public Command
{
	public:
		PackageReductionDiscount() : Command() {}
		PackageReductionDiscount(const PackageReductionDiscount &other) : Command(other) {}
		PackageReductionDiscount(const unsigned int id, const order_date &date, const std::string &client) : Command(id, date, client) {}
		PackageReductionDiscount &operator=(const PackageReductionDiscount &other) { Command::operator=(other); return (*this); }
		~PackageReductionDiscount() {}

		float get_total_price() const
		{
			const float fair_price = calculate_fair_price();
			return (fair_price - (fair_price > 150.f ? 10.f : 0.f));
		}
};

#endif
