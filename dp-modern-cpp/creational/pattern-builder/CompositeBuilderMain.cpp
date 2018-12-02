#include "Person.h"
#include "PersonBuilder.h"
#include "PersonAddressBuilder.h"
#include "PersonJobBuilder.h"
#include <iostream>

using std::cout;
using std::endl;

int main() {
    Person p = Person::create()
        .lives().at("612 Bristol Trce").with_postcode("30022").in("Alpharetta GA")
        .works().at("Intralot").as_a("Manager Terminal SW").earning(100000);
    cout << p << endl;
    return EXIT_SUCCESS;
}
