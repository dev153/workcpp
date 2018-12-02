#pragma once

#include "PersonBuilder.h"

class PersonAddressBuilder : public PersonBuilderBase {
public:
    explicit PersonAddressBuilder(Person& person)
    : PersonBuilderBase{person}
    {}
    PersonAddressBuilder& at(const std::string& street_address) {
        person.street_address = street_address;
        return *this;
    }
    PersonAddressBuilder& with_postcode(const std::string& post_code) {
        person.post_code = post_code;
        return *this;
    }
    PersonAddressBuilder& in(const std::string& city) {
        person.city = city;
        return *this;
    }
};