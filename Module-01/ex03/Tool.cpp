#include "Tool.hpp"

Tool::Tool() : _number_of_uses(0), _owner()
{
	std::cout << "Tool default-constructed" << std::endl;
}

Tool::~Tool()
{
	std::cout << "Tool(_number_of_uses: " << _number_of_uses;
	if (_owner)
		std::cout << ", owner: " << *_owner;
	std::cout << ") destroyed" << std::endl;
	if (_owner)
		_owner->remove_tool(this);
}

void Tool::increment_usage()
{
	if (!_owner)
		throw std::runtime_error("Tool without an owner can't be used");
	++_number_of_uses;
}

void Tool::set_owner(Worker *owner)
{
	if (!owner) return ;
	if (!_owner)
		_owner->unequip(this);
	_owner = owner;
	_owner->equip(this);
}

int Tool::get_number_of_uses() const
{
	return (_number_of_uses);
}

std::ostream &operator<<(std::ostream &o, const Tool &t)
{
	o << "Tool(number_of_uses: " << t.get_number_of_uses();
	if (t.get_owner())
		o << ", owner: " << *t.get_owner();
	o << ")";
	return (o);
}
