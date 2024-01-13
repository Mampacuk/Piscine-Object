#ifndef WORKER_HPP
# define WORKER_HPP

# include "Position.hpp"
# include "Statistic.hpp"

// COMPOSITION:
//
// composition is closely related ways to combine objects or data types
// into more complex ones. object composition is about combining
// objects within compound objects, and at the same time, ensuring
// the encapsulation of each object by using their well-defined interface
// without visibility of their internals. In this regard, object composition
// differs from data structures, which do not enforce encapsulation.
// composition can be regarded as a relationship between types: an object
// of a composite type (e.g. car) "has" objects of other types (e.g. wheel).
//
// composition must be distinguished from subtyping, which is the process of
// adding detail to a general data type to create a more specific data type.
// For instance, cars may be a specific type of vehicle: car is a vehicle.
// subtyping doesn't describe a relationship between different objects,
// but instead, says that objects of a type are simultaneously objects of another type.
// 
// src: https://en.wikipedia.org/wiki/Object_composition
// 
// say, composition is good when you need properties/functionality that are common in classes
// that are drastically (!) different: it avoids the interfaces (contracts) that are enforced
// by inheritance, also prevent unwanted polymorphism.
// example: both Player and Enemy have a Position. However, win_game(...) shouldn't expect
// anyone who has a Position, so we expect concrete type instead of polymorphism. or, both have Healthbar,
// but only for Player replenish_health(...) must be usable => don't expose Healthbar's replenishing methods
// in the Enemy class, but do so for the Player.
class Worker
{
	private:
		Position coordonnee;
		Statistic stat;
	public:
		Worker();
		~Worker();
		Worker(const Position &coordonnee, const Statistic &stat);
		Worker(const Worker &copy);
		Worker &operator=(const Worker &copy);
		int get_x() const;
		int get_y() const;
		int get_z() const;
		int get_level() const;
		int get_exp() const;
};

std::ostream &operator<<(std::ostream &o, const Worker &w);

#endif
