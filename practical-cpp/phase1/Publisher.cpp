#include "Exception.h"
#include "Observer.h"
#include "Publisher.h"

#include <sstream>
#include <unordered_map>
#include <utility>

using std::make_pair;
using std::make_unique;
using std::ostringstream;
using std::shared_ptr;
using std::string;
using std::unique_ptr;
using std::unordered_map;

class Publisher::PublisherImpl {
    using ObserversList = unordered_map<string, unique_ptr<Observer>>;
    using Events = std::unordered_map<string,ObserversList>;
public:
    PublisherImpl();
    ~PublisherImpl();

    void attach(const std::string& eventName,std::unique_ptr<Observer> observer);
    std::unique_ptr<Observer> detach(const std::string & eventName, const std::string& observerName);
    void notify(const string& eventName, shared_ptr<EventData> eventData);

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
    return m_publisherImpl->detach(eventName,observerName);
}
void Publisher::raise(const std::string &eventName, std::shared_ptr<EventData> eventData) const {
    m_publisherImpl->notify(eventName,eventData);
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
    // [1] Find the observers list that corresponds to the event name.
    auto observersListIt = findCheckedEvent(eventName);
    // [2] Obtain a reference to the found observers list.
    //     If not found an exception will be thrown from the findCheckedEvent() method.
    auto& observersList = observersListIt->second;
    // [3] Need to make sure that the observer has not already been attached for this event name.
    auto observerIt = observersList.find(observer->name());
    // [4] If already attched throw an exception
    if ( observerIt != observersList.end() ) {
        throw Exception("Observer already attached to publisher.");
    }
    // [5] Otherwise insert. NOTE: The unique_ptr has to be moved at this point.
    observersList.insert(make_pair(observer->name(),move(observer)));
}
std::unique_ptr<Observer> Publisher::PublisherImpl::detach( const std::string &eventName,
                                                            const std::string &observerName) {
    // [1] Find the observers list that corresponds to the event name.
    auto observersListIt = findCheckedEvent(eventName);
    // [2] Obtain a reference to the found observers list.
    //     If not found an exception will be thrown from the findCheckedEvent() method.
    auto& observersList = observersListIt->second;
    // [3] Need to make sure that the observer has been attached for this event name.
    auto observerIt = observersList.find(observerName);
    if ( observerIt == observersList.end() ) {
        throw Exception("Cannot detach observer because observer not found.");
    }
    // [4] The observer is found. First reclaim ownership since the pointer is a unique_ptr.
    //auto observerPtr = move(observerIt->second);
    auto observerPtr = move(observerIt->second);
    // [5] Erase the observer based on the name which is the key of the unordered_map.
    observersList.erase(observerName);

    return observerPtr;
}

void Publisher::PublisherImpl::notify(const std::string &eventName, shared_ptr<EventData> eventData) {
    // [1] Find the observers list that corresponds to the event name.
    auto observersListIt = findCheckedEvent(eventName);
    // [2] Obtain a reference to the found observers list.
    //     If not found an exception will be thrown from the findCheckedEvent() method.
    auto& observersList = observersListIt->second;
    for ( const auto & observerPair: observersList  ) {
        observerPair.second->notify(eventData);
    }
    return;
}

Publisher::PublisherImpl::Events::iterator Publisher::PublisherImpl::findCheckedEvent(
        const std::string &eventName) {
    auto eventIt = m_events.find(eventName);
    if ( eventIt == m_events.end() ) {
        ostringstream oss;
        oss << "Publisher does not support event '" << eventName << "'";
        throw Exception{oss.str()};
    }
    return eventIt;
}
Publisher::PublisherImpl::Events::const_iterator Publisher::PublisherImpl::findCheckedEvent(
        const std::string &eventName) const {
    auto eventIt = m_events.find(eventName);
    if ( eventIt == m_events.end() ) {
        ostringstream oss;
        oss << "Publisher does not support event '" << eventName << "'";
        throw Exception{oss.str()};
    }
    return eventIt;
}
