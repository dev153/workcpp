#pragma once
#include "Person.h"

class PersonAddressBuilder;
class PersonJobBuilder;

class PersonBuilderBase {
protected:
    // This is a reference to the object that is to be created.
    // The actual object will be created from the PersonBuilder class that follows.
    Person& person;
public:
    explicit PersonBuilderBase(Person& person)
    : person{person}
    {}

    // Conversion operator is required so as to to obtain the Person object.
    // What is returned is a reference that is stored.
    operator Person() const {
        return std::move(person);
    }

    PersonAddressBuilder lives() const;
    PersonJobBuilder works() const;
};

class PersonBuilder : public PersonBuilderBase {
private:
    // This is the actual project to be constructed.
    Person person;
public:
    // Consturctor which will initialize the parent class with the desired Person project.
    PersonBuilder();
};