#include "MyManagedObject.h"
#include <cstdint>
#include <cstdlib>

using std::stack;
using std::mutex;

MyManagedObject::MyManagedObjectCollection MyManagedObject::s_ManagedObjects{};
stack<unsigned int> MyManagedObject::s_FreeList{};
mutex MyManagedObject::s_mutex;


MyManagedObject::MyManagedObject(unsigned int value)
    : m_Value(value)
{

}
void *MyManagedObject::operator new(size_t numBytes) {
    void* objectMemory{};
    s_mutex.lock();
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
    s_mutex.unlock();
    return objectMemory;
}
void MyManagedObject::operator delete(void *pMem) {
    s_mutex.lock();
    const intptr_t index {
        ( static_cast<MyManagedObject*>(pMem) - s_ManagedObjects.data() ) /
          static_cast<intptr_t>(sizeof(MyManagedObject) ) };
    if ( 0 <= index && index < static_cast<intptr_t>(s_ManagedObjects.size()) ) {
        s_FreeList.emplace(static_cast<unsigned int>(index));
    } else {
        free(pMem);
    }
    s_mutex.unlock();
}
