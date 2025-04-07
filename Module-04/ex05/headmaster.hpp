#ifndef HEADMASTER_HPP
# define HEADMASTER_HPP

# include "common.hpp"
# include "staff.hpp"
# include "observer.hpp"

class Headmaster : public Staff, public Observer, public std::enable_shared_from_this<Headmaster>
{
private:
	std::vector<std::shared_ptr<Form>> _formToValidate;
	std::weak_ptr<School> _school;
	std::shared_ptr<Bell> _bell;
	
public:
	Headmaster() = default;
	Headmaster(Headmaster&&) = default;
	Headmaster(const Headmaster&) = default;
	Headmaster(const std::string &p_name, std::weak_ptr<School> school);
	Headmaster &operator=(const Headmaster&) = default;
	~Headmaster() = default;

	std::weak_ptr<Form> receiveForm(std::shared_ptr<Form> p_form);
	std::ostream &print_forms(std::ostream &o = std::cout) const { return (ft::print_shared_ptr_container_object(o, _formToValidate)); }
	std::weak_ptr<Form> request_form(FormType form_type);
	void sign_and_execute(std::weak_ptr<Form> form);
	void sign_and_execute_all_forms();
	void make_professors_do_class() const;
	void on_event(Event event) override;
	Bell &get_bell() { return (*_bell); }
	void ring_bell();
};

std::ostream &operator<<(std::ostream &o, const Headmaster &h);

#endif
