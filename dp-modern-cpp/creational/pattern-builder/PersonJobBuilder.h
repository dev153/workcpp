#pragma once 

#include "PersonBuilder.h"

class PersonJobBuilder : public PersonBuilderBase {
public:
    explicit PersonJobBuilder(Person& person) 
    : PersonBuilderBase{person}
    {}
    PersonJobBuilder at(const std::string& company_name) {
        person.company_name = company_name;
        return *this;
    }
    PersonJobBuilder as_a(const std::string& position) {
        person.position = position;
        return *this;
    }
    PersonJobBuilder earning(const int annual_income) {
        person.annual_income = annual_income;
        return *this;
    }
};