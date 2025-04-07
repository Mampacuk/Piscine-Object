#ifndef STAFF_HPP
# define STAFF_HPP

# include "common.hpp"
# include "person.hpp"

class Staff : public Person
{
private:

public:
	Staff() = default;
	Staff(Staff&&) = default;
	Staff(const Staff&) = default;
	Staff(const std::string &p_name) : Person(p_name) {}
	Staff &operator=(const Staff&) = default;
	virtual ~Staff() = default;
	// @return true if signing was successful
	bool sign(std::weak_ptr<Form> p_form);
};

std::ostream &operator<<(std::ostream &o, const Staff &s);

#endif
