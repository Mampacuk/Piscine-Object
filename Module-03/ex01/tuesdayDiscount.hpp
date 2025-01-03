#ifndef TUESDAYDISCOUNT_HPP
# define TUESDAYDISCOUNT_HPP

# include "command.hpp"

class TuesdayDiscountCommand : public Command
{
	public:
		TuesdayDiscountCommand() : Command() {}
		TuesdayDiscountCommand(const TuesdayDiscountCommand &other) : Command(other) {}
		TuesdayDiscountCommand(const unsigned int id, const order_date &date, const std::string &client) : Command(id, date, client) {}
		TuesdayDiscountCommand &operator=(const TuesdayDiscountCommand &other) { Command::operator=(other); return (*this); }
		~TuesdayDiscountCommand() {}

		float get_total_price() const
		{
			return (calculate_fair_price() * (get_order_date().tm_wday == 2 ? 0.9f : 1.f));
		}
};

#endif
