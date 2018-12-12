#pragma once

#include "Publisher.h"

#include <memory>
#include <string>
#include <vector>

class StackEventData : public EventData {
public:
    enum class ErrorConditions { Empty, TooFewArguments };
    StackEventData(ErrorConditions err) : m_err(err) {}

    static const char * Message(ErrorConditions ec);
    const char* messsage() const;
    ErrorConditions error() const {
        return m_err;
    }
private:
    ErrorConditions m_err;
};

class Stack : public Publisher {
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

    static const std::string StackChanged;
    static const std::string StackError;

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
