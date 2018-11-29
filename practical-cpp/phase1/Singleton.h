#pragma once

class Singleton {
public:
    static Singleton& Instance();
    int getSolution();
private:
    Singleton() {};
    Singleton(const Singleton&)  = delete;
    Singleton& operator=(const Singleton&) = delete;
    Singleton(Singleton&&) = delete;
    Singleton& operator=(Singleton&&) = delete;
    ~Singleton(){}
};
