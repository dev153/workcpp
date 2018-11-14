#include "MyManagedObject.h"
#include <cstdlib>
#include <iostream>

int main(){
    using std::cout;
    using std::endl;

    cout << std::hex << std::showbase;
    MyManagedObject* pObject1 {new MyManagedObject(1)};
    cout << "pObject1: " << pObject1 << endl;
    MyManagedObject* pObject2 {new MyManagedObject(2)};
    cout << "pObject2: " << pObject2 << endl;

    delete pObject1;
    pObject1 = nullptr;

    MyManagedObject* pObject3 {new MyManagedObject(3)};
    cout << "pObject3: " << pObject3 << endl;
    MyManagedObject* pObject4 {new MyManagedObject(4)};
    cout << "pObject4: " << pObject4 << endl;

    delete pObject2;
    pObject2 = nullptr;

    delete pObject3;
    pObject3 = nullptr;

    delete pObject4;
    pObject4 = nullptr;

    return EXIT_SUCCESS;
}
