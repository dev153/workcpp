#include "Singleton.h"

Singleton& Singleton::Instance() {
    static Singleton instance;
    return instance;
}

int Singleton::getSolution() {
    return 42;
}
