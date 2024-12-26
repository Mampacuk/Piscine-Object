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
		_owner->unequip(this);
}

void Tool::increment_usage()
{
	if (!_owner)
		throw std::runtime_error("Tool without an owner can't be used");
	++_number_of_uses;
}

const Worker *Tool::get_owner() const
{
	return (_owner);
}

void Tool::set_owner(Worker *new_owner)
{
	if (_owner)
		_owner->unequip(this);
	_owner = new_owner;
	if (_owner)
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
