#ifndef HEADMASTER_HPP
# define HEADMASTER_HPP

# include "common.hpp"
# include "staff.hpp"

class Headmaster : public Staff
{
private:
	std::vector<std::shared_ptr<Form>> _formToValidate;
	
public:
	Headmaster() = default;
	Headmaster(Headmaster&&) = default;
	Headmaster(const Headmaster&) = default;
	Headmaster(const std::string &p_name) : Staff(p_name) {}
	Headmaster &operator=(const Headmaster&) = default;
	~Headmaster() = default;

	void receiveForm(std::shared_ptr<Form> p_form)
	{
		if (p_form)
		{
			std::cout << *this << " received a " << *p_form << std::endl;
			_formToValidate.push_back(std::move(p_form));
		}
	}
	void sign_forms() { ft::erase_if(_formToValidate, [this](const std::shared_ptr<Form> &f) { return (sign(f)); }); }
	std::ostream &print_forms(std::ostream &o = std::cout) const { return (ft::print_shared_ptr_container_object(o, _formToValidate)); }
};

std::ostream &operator<<(std::ostream &o, const Headmaster &h);

#endif
