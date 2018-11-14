#ifndef MY_MANAGED_OBJECT_H_
#define MY_MANAGED_OBJECT_H_

#include <stack>
#include <thread>
#include <vector>

class MyManagedObject {
private:
    // static const unsigned int MAX_OBJECTS{8};
    static thread_local const unsigned int MAX_OBJECTS;

    using MyManagedObjectCollection = std::vector<MyManagedObject>;
    // static MyManagedObjectCollection s_ManagedObjects;
    static thread_local MyManagedObjectCollection s_ManagedObjects;
    // static std::stack<unsigned int> s_FreeList;
    static thread_local std::stack<unsigned int> s_FreeList;
    unsigned int m_Value{0xFFFFFFFF};
public:
    MyManagedObject() = default;
    MyManagedObject(unsigned int value);
    void* operator new(size_t numBytes);
    void operator delete(void* pMem);
};

#endif
