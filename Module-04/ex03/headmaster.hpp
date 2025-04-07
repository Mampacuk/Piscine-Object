#ifndef HEADMASTER_HPP
# define HEADMASTER_HPP

# include "common.hpp"
# include "staff.hpp"

// Headmaster is the Mediator class, and Student and Professor are its colleagues.
// Student and Professor have an indirect link to Headmaster via School.
class Headmaster : public Staff
{
private:
	std::vector<std::shared_ptr<Form>> _formToValidate;
	std::weak_ptr<School> _school;
	
public:
	Headmaster() = default;
	Headmaster(Headmaster&&) = default;
	Headmaster(const Headmaster&) = default;
	Headmaster(const std::string &p_name, std::weak_ptr<School> school) : Staff(p_name), _school(std::move(school)) {}
	Headmaster &operator=(const Headmaster&) = default;
	~Headmaster() = default;

	std::weak_ptr<Form> receiveForm(std::shared_ptr<Form> p_form);
	std::ostream &print_forms(std::ostream &o = std::cout) const { return (ft::print_shared_ptr_container_object(o, _formToValidate)); }
	std::weak_ptr<Form> request_form(FormType form_type);
	void sign_and_execute(std::weak_ptr<Form> form);
	void sign_and_execute_all_forms();
	void make_professors_do_class() const;
};

std::ostream &operator<<(std::ostream &o, const Headmaster &h);

#endif
