#pragma once

#include <string>
#include <iostream>

class PersonBuilder;

class Person {
    private:
        // address
        std::string street_address;
        std::string post_code;
        std::string city;
        // employment
        std::string company_name;
        std::string position;
        int annual_income;
        // Leave constructor empty since a composite builder will be used to create the object.
        Person();
        Person(const Person& other);
        Person& operator=(const Person& other);

    public:
        ~Person();
        // Move semantics must be implemented because at the end of the object construction
        // The object PersonBuilderBase either under the PersonAddressBuilder or PersonJobBuilder facet
        // it has to be converted to a Person object. 
        Person(Person&& other);
        Person& operator=(Person&& other);

        // This is the starting point function for creating a Person object.
        static PersonBuilder create();

        friend std::ostream& operator<<(std::ostream& os, const Person& person);

    friend class PersonBuilder;
    friend class PersonAddressBuilder;
    friend class PersonJobBuilder;
};