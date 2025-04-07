#include "rooms.hpp"

std::ostream &operator<<(std::ostream &o, const Room &r)
{
	o << "Room(ID: " << r.id() <<  ", occupants: ";
	return (r.print_occupants(o) << ")");
}

std::ostream &operator<<(std::ostream &o, const Classroom &c)
{
	o << "Classroom(currentRooom: ";
	return (ft::print_shared_ptr(o, c.current_course()) << ", " << static_cast<const Room&>(c) << ")");
}

std::ostream &operator<<(std::ostream &o, const SecretarialOffice &s)
{
	o << "SecretarialOffice(archivedForms: ";
	return (s.printArchivedForms(o) << ", " << static_cast<const Room&>(s) << ")");
}

std::ostream &operator<<(std::ostream &o, const HeadmasterOffice &h)
{
	return (o << "HeadmasterOffice(" << static_cast<const Room&>(h) << ")");
}

std::ostream &operator<<(std::ostream &o, const StaffRestRoom &s)
{
	return (o << "StaffRestRoom(" << static_cast<const Room&>(s) << ")");
}

std::ostream &operator<<(std::ostream &o, const Courtyard &c)
{
	return (o << "Courtyard(" << static_cast<const Room&>(c) << ")");
}
