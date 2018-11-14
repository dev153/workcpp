#include "MyManagedObject.h"
#include <cstdlib>
#include <iostream>
#include <thread>

using std::cout;
using std::endl;
using std::thread;

void ThreadTask() {
    MyManagedObject* pObject4 {new MyManagedObject(5)};
    cout << "pObject4: " << pObject4 << endl;
    MyManagedObject* pObject5 {new MyManagedObject(6)};
    cout << "pObject5: " << pObject5 << endl;

    delete pObject4;
    pObject4 = nullptr;

    MyManagedObject* pObject6 {new MyManagedObject(7)};
    cout << "pObject6: " << pObject6 << endl;
    pObject4 = new MyManagedObject(8);
    cout << "pObject4: " << pObject4 << endl;

    delete pObject5;
    pObject5 = nullptr;

    delete pObject6;
    pObject6 = nullptr;

    delete pObject4;
    pObject4 = nullptr;
}

int main(){
    cout << std::hex << std::showbase;
    thread myThread{ThreadTask};

    MyManagedObject* pObject1 {new MyManagedObject(1)};
    cout << "pObject1: " << pObject1 << endl;
    MyManagedObject* pObject2 {new MyManagedObject(2)};
    cout << "pObject2: " << pObject2 << endl;

    delete pObject1;
    pObject1 = nullptr;

    MyManagedObject* pObject3 {new MyManagedObject(3)};
    cout << "pObject3: " << pObject3 << endl;
    pObject1 = new MyManagedObject(4);
    cout << "pObject1: " << pObject1 << endl;

    delete pObject2;
    pObject2 = nullptr;

    delete pObject3;
    pObject3 = nullptr;

    delete pObject1;
    pObject1 = nullptr;

    myThread.join();

    return EXIT_SUCCESS;
}
