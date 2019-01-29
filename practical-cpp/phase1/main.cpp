#include <cstdlib>
#include <iostream>
#include <typeinfo>

#include "Singleton.h"
#include "Stack.h"
#include "TestStack.h"

using std::cout;
using std::endl;

int main() {
    cout << Singleton::Instance().getSolution() << endl;
    Stack & stack = Stack::Instance();
    TestStack::test();
    return EXIT_SUCCESS;
}
