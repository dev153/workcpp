#include "MyManagedObject.h"
#include <cstdint>
#include <cstdlib>

using std::stack;

thread_local const unsigned int MyManagedObject::MAX_OBJECTS{8};
thread_local MyManagedObject::MyManagedObjectCollection MyManagedObject::s_ManagedObjects{};
thread_local stack<unsigned int> MyManagedObject::s_FreeList{};

MyManagedObject::MyManagedObject(unsigned int value)
    : m_Value(value)
{

}
void *MyManagedObject::operator new(size_t numBytes) {
    void* objectMemory{};
    if (s_ManagedObjects.capacity() < MAX_OBJECTS) {
        s_ManagedObjects.reserve(MAX_OBJECTS);
    }
    if(numBytes == sizeof(MyManagedObject) && s_ManagedObjects.size() < s_ManagedObjects.capacity()) {
        unsigned int index{0xFFFFFFFF};
        if(s_FreeList.size() > 0) {
            index = s_FreeList.top();
            s_FreeList.pop();
        }
        if (index == 0xFFFFFFFF){
            s_ManagedObjects.push_back({});
            index = static_cast<unsigned int>(s_ManagedObjects.size() - 1);
        }
        objectMemory = s_ManagedObjects.data() + index;
    } else {
        objectMemory = malloc(numBytes);
    }
    return objectMemory;
}
void MyManagedObject::operator delete(void *pMem) {
    const intptr_t index {
        ( static_cast<MyManagedObject*>(pMem) - s_ManagedObjects.data() ) /
          static_cast<intptr_t>(sizeof(MyManagedObject) ) };
    if ( 0 <= index && index < static_cast<intptr_t>(s_ManagedObjects.size()) ) {
        s_FreeList.emplace(static_cast<unsigned int>(index));
    } else {
        free(pMem);
    }
}
