#include "Exception.h"
#include "Publisher.h"

#include <sstream>
#include <unordered_map>
#include <utility>

using std::make_pair;
using std::make_unique;
using std::ostringstream;
using std::string;
using std::unique_ptr;
using std::unordered_map;

class Observer {
public:
    Observer(){}
    ~Observer(){}
    string name() {
        return "";
    }
private:
};

class Publisher::PublisherImpl {
    using ObserversList = unordered_map<string, unique_ptr<Observer>>;
    using Events = std::unordered_map<string,ObserversList>;
public:
    PublisherImpl();
    ~PublisherImpl();

    void attach(const std::string& eventName,std::unique_ptr<Observer> observer);
    std::unique_ptr<Observer> detach(const std::string & eventName, const std::string& observerName);

    Events::const_iterator findCheckedEvent(const string& eventName) const;
    Events::iterator findCheckedEvent(const string& eventName);
private:
    Events m_events;
};


//=============================================================================
//
//  Publisher class implementation.
//
//=============================================================================

Publisher::Publisher()
    : m_publisherImpl(make_unique<PublisherImpl>()){
}
Publisher::~Publisher() {

}
void Publisher::attach(const std::string &eventName, std::unique_ptr<Observer> observer) {
    m_publisherImpl->attach(eventName,std::move(observer));
    return;
}
std::unique_ptr<Observer> Publisher::detach(const std::string &eventName, const std::string &observerName) {
    return make_unique<Observer>();
}

//=============================================================================
//
//  PublisherImpl class implementation.
//
//=============================================================================




Publisher::PublisherImpl::PublisherImpl() {

}
Publisher::PublisherImpl::~PublisherImpl()
{

}
void Publisher::PublisherImpl::attach(const std::string &eventName, std::unique_ptr<Observer> observer) {
}
std::unique_ptr<Observer> Publisher::PublisherImpl::detach(const std::string &eventName, const std::string &observerName) {

}

Publisher::PublisherImpl::Events::iterator Publisher::PublisherImpl::findCheckedEvent(const std::string &eventName) {
    auto eventIt = m_events.find(eventName);
    if ( eventIt == m_events.end() ) {
        ostringstream oss;
        oss << "Publisher does not support event '" << eventName << "'";
        throw Exception{oss.str()};
    }
    return eventIt;
}
Publisher::PublisherImpl::Events::const_iterator Publisher::PublisherImpl::findCheckedEvent(const std::string &eventName) const {
    auto eventIt = m_events.find(eventName);
    if ( eventIt == m_events.end() ) {
        ostringstream oss;
        oss << "Publisher does not support event '" << eventName << "'";
        throw Exception{oss.str()};
    }
    return eventIt;
}
