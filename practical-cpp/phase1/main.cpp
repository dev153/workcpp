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

    stack.push(42.1);
    stack.push(42.2);
    cout << stack.toString() << endl;

    TestStack::test();

    return EXIT_SUCCESS;
}
