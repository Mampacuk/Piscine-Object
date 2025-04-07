#ifndef SECRETARY_HPP
# define SECRETARY_HPP

# include "common.hpp"
# include "staff.hpp"
# include "observer.hpp"

class Secretary : public Staff, public Observer, public std::enable_shared_from_this<Secretary>
{
	std::weak_ptr<School> _school;
public:
	Secretary() = default;
	Secretary(Secretary&&) = default;
	Secretary(const Secretary&) = default;
	Secretary(const std::string &p_name, std::weak_ptr<School> school) : Staff(p_name), _school(std::move(school)) {}
	Secretary &operator=(const Secretary&) = default;
	~Secretary() = default;

	std::shared_ptr<Form> createForm(FormType p_formType);
	void on_event(Event event) override;
};

std::ostream &operator<<(std::ostream &o, const Secretary &s);

#endif
