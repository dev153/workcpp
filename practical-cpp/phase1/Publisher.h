#pragma once

#include <memory>
#include <set>
#include <string>
#include <vector>

class Observer;

class EventData {
public:
    virtual ~EventData();
};

class Publisher {
private:
    class PublisherImpl;
public:
    Publisher();
    ~Publisher();
    void attach(const std::string& eventName,std::unique_ptr<Observer> observer);
    std::unique_ptr<Observer> detach(const std::string& eventName, const std::string& observerName);
    std::set<std::string> listEvents() const;
    std::set<std::string> listEventObservers(const std::string& eventName) const;
protected:
    void raise(const std::string& eventName, std::shared_ptr<EventData> eventData) const;
    void registerEvent(const std::string& eventName);
    void registerEvents(const std::vector<std::string>& eventNames);
private:
    std::unique_ptr<PublisherImpl> m_publisherImpl;
};
