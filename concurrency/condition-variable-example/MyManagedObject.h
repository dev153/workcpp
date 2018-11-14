#ifndef MY_MANAGED_OBJECT_H_
#define MY_MANAGED_OBJECT_H_

#include <mutex>
#include <stack>
#include <vector>

class MyManagedObject {
private:
    static const unsigned int MAX_OBJECTS{8};
    using MyManagedObjectCollection = std::vector<MyManagedObject>;
    static MyManagedObjectCollection s_ManagedObjects;
    static std::stack<unsigned int> s_FreeList;

    static std::mutex s_mutex;

    unsigned int m_Value{0xFFFFFFFF};
public:
    MyManagedObject() = default;
    MyManagedObject(unsigned int value);
    unsigned int GetValue();
    void* operator new(size_t numBytes);
    void operator delete(void* pMem);
};

#endif
