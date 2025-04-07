#ifndef FORM_HPP
# define FORM_HPP

# include "common.hpp"

// Form is the command class that has the mandatory execute() method.
class Form
{
private:
	FormType _formType;
	bool _signed;
public:
	Form() = default;
	Form(Form&&) = default;
	Form(const Form&) = default;
	Form(FormType p_formType) : _formType(p_formType), _signed(false) {}
	Form &operator=(const Form&) = default;
	virtual ~Form() = default;

	FormType form_type() const { return (_formType); }
	virtual bool is_complete() const = 0;
	// can only be signed by the headmaster 
	// @return true if Form got signed. it will iff it is complete
	bool get_signed(const Staff &staff);
	// @return true if Form got executed. it will iff it is signed
	bool execute();
private:
	virtual void execute_impl() = 0;
};

std::ostream &operator<<(std::ostream &o, const Form &f);

#endif
