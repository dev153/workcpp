#pragma once

#include <memory>
#include <string>
#include <vector>

class Stack {
private:
    class StackImpl;
public:
    static Stack& Instance();
    void push(double);
    double pop();
    std::string toString();
    void getElements(size_t, std::vector<double>&) const;
    void swapTop();
    // these are just needed for testing
    size_t size() const;
    void clear() const;
private:
    Stack();
    ~Stack();
    /* Block copy contructor, move constructor, assignment operator, move assignment operator. */
    Stack(const Stack&) = delete;
    Stack& operator=(const Stack&) = delete;
    Stack(Stack&&) = delete;
    Stack& operator=(Stack&&) = delete;
    std::unique_ptr<StackImpl> m_pimpl;
};
