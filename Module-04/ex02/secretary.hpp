#ifndef SECRETARY_HPP
# define SECRETARY_HPP

# include "common.hpp"
# include "staff.hpp"

class Secretary : public Staff
{
private:

public:
	Secretary() = default;
	Secretary(Secretary&&) = default;
	Secretary(const Secretary&) = default;
	Secretary(const std::string &p_name) : Staff(p_name) {}
	Secretary &operator=(const Secretary&) = default;
	~Secretary() = default;

	std::shared_ptr<Form> createForm(FormType p_formType);
	void archiveForm();
};

std::ostream &operator<<(std::ostream &o, const Secretary &s);

#endif
