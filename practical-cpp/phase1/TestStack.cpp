#include "Stack.h"
#include "TestStack.h"

#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

void TestStack::test() {
    Stack & instance = Stack::Instance();
    instance.push(1.2);
    instance.push(2.3);
    instance.push(3.4);
    cout << instance.toString() << endl;
}
