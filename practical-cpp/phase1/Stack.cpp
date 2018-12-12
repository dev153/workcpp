#include "Stack.h"

#include <algorithm>
#include <deque>
#include <sstream>

using std::deque;
using std::make_unique;
using std::string;
using std::vector;

const string Stack::StackChanged = "stackChanged";
const string Stack::StackError = "error";

//=============================================================================
//
//  StackEventData class implementation.
//
//=============================================================================


const char *StackEventData::Message(StackEventData::ErrorConditions ec) {
    switch(ec) {
    case ErrorConditions::Empty:
        return "Attempting to pop an empty stack.";
    case ErrorConditions::TooFewArguments:
        return "Need at least two stack elements to swap top.";
    default:
        return "Unknown error.";
    };
}

const char *StackEventData::messsage() const
{
    return Message(m_err);
}

//=============================================================================
//
//  StackImpl class declaration.
//
//=============================================================================

class Stack::StackImpl  {
public:
    explicit StackImpl();
    ~StackImpl(){}
    void push(double value);
    double pop();
    void getElements(size_t n, vector<double>& v) const;
    void swapTop();

    std::string toString();
    size_t size() const;
    void clear();
private:
    deque<double> m_stack;
};

//=============================================================================
//
//  Stack class implementation.
//
//=============================================================================

Stack &Stack::Instance() {
    static Stack instance;
    return instance;
}

void Stack::push(double value) {
    m_pimpl->push(value);
}

double Stack::pop() {
    return m_pimpl->pop();
}

std::string Stack::toString() {
    return m_pimpl->toString();
}

void Stack::getElements(size_t n, std::vector<double> &v) const
{
    m_pimpl->getElements(n,v);
    return;
}

void Stack::swapTop()
{
    m_pimpl->swapTop();
    return;
}

size_t Stack::size() const {
    return m_pimpl->size();
}

void Stack::clear() const {
    m_pimpl->clear();
}

Stack::Stack() : m_pimpl(make_unique<StackImpl>()){
    registerEvent(StackChanged);
    registerEvent(StackError);
}

Stack::~Stack() {

}

//=============================================================================
//
//  StackImpl class implementation.
//
//=============================================================================

Stack::StackImpl::StackImpl() : m_stack() {

}

void Stack::StackImpl::push(double value) {
    m_stack.push_back(value);
}

double Stack::StackImpl::pop()
{
    if ( m_stack.empty() ) {
        return -1;
        //TODO: An exception must be thrown at this point.
    } else {
        auto value = m_stack.back();
        m_stack.pop_back();
        return value;
    }
}

void Stack::StackImpl::getElements(size_t n, vector<double> &v) const
{
    if ( n > m_stack.size() ) {
        n = m_stack.size();
    }

    v.insert(v.end(), m_stack.rbegin(), m_stack.rbegin() + n );
}

void Stack::StackImpl::swapTop()
{
    if ( 2 > m_stack.size() ) {
        //TODO: An exception must be thrown at this point.
    }
    auto first = m_stack.back();
    m_stack.pop_back();
    auto second = m_stack.back();
    m_stack.pop_back();
    m_stack.push_back(first);
    m_stack.push_back(second);
}

std::string Stack::StackImpl::toString() {
    using std::ostringstream;
    ostringstream oss;
    oss << "[";
    if ( m_stack.size() > 0 ) {
        oss << *m_stack.begin();
        for_each(m_stack.begin()+1, m_stack.end(), [&](double value) {
            oss << "," << value;
        });
    }
    oss << "]";
    return oss.str();
}

size_t Stack::StackImpl::size() const {
    return m_stack.size();
}

void Stack::StackImpl::clear() {
    m_stack.clear();
}



