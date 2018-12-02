#include "Person.h"
#include "PersonBuilder.h"

#include <iostream>

using std::cout;
using std::endl;
using std::ostream;

Person::Person() {
    cout << "Person constructor\n";
}

Person::Person(const Person& other) {
    cout << "Person copy constructor" << endl;
    street_address = other.street_address;
    post_code = other.post_code;
    city = other.city;
    company_name = other.company_name;
    position = other.position;
    annual_income = other.annual_income;
}
    
Person& Person::operator=(const Person& other) {
    cout << "Person assignment operator" << endl;
    if ( this == &other ) {
        return *this;
    }
    street_address = other.street_address;
    post_code = other.post_code;
    city = other.city;
    company_name = other.company_name;
    position = other.position;
    annual_income = other.annual_income;
    return *this;
}

Person::~Person() {
    cout << "Person destructor\n";
}

PersonBuilder Person::create() {
    return PersonBuilder{};
}

Person::Person(Person&& other)
: street_address{move(other.street_address)}
, post_code{move(other.post_code)}
, city{move(other.city)}
, company_name{move(other.company_name)}
, position{move(other.position)}
, annual_income{other.annual_income}
{
    cout << "Person move constructor" << endl;
}
Person& Person::operator=(Person&& other) {
    cout << __FUNCTION__ << endl;
    if ( this == &other ) {
        return *this;
    }
    street_address = move(other.street_address);
    post_code = move(other.post_code);
    city = move(other.city);
    company_name = move(other.position);
    position = move(other.position);
    annual_income = other.annual_income;
    return *this;
}

ostream& operator<<(ostream& os, const Person& person) {
    return os 
        << "street_address: " << person.street_address
        << " post_code: " << person.post_code
        << " city: " << person.city
        << " company_name: " << person.company_name
        << " position: " << person.position
        << " annual_income: " << person.annual_income;
}