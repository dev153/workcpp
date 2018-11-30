#pragma once

#include <memory>
#include <string>

class EventData;

class Observer {
public:
    explicit Observer(const std::string name);
    virtual ~Observer();
    void notify(std::shared_ptr<EventData> eventData);
    const std::string name() const;
private:
    std::string m_name;
};
