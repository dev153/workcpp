#pragma once

#include <memory>
#include <string>

class Observer;

class Publisher {
private:
    class PublisherImpl;
public:
    Publisher();
    ~Publisher();
    void attach(const std::string& eventName,std::unique_ptr<Observer> observer);
    std::unique_ptr<Observer> detach(const std::string & eventName, const std::string& observerName);
private:
    std::unique_ptr<PublisherImpl> m_publisherImpl;
};
