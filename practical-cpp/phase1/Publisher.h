#pragma once

#include <memory>
#include <string>

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
protected:
    void raise(const std::string& eventName, std::shared_ptr<EventData> eventData) const;
private:
    std::unique_ptr<PublisherImpl> m_publisherImpl;
};
