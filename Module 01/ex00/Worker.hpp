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
class Worker
{
    private:
        Position coordonnee;
        Statistic stat;
    public:
        Worker();
        ~Worker();
        Worker(const Worker &copy);
        Worker &operator=(const Worker &copy);
};

#endif
