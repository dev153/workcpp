#include "Observer.h"

using std::string;

Observer::Observer(const string name) : m_name(name) {
}
Observer::~Observer() {
}
void Observer::notify(std::shared_ptr<EventData> eventData) {
}
const std::string Observer::name() const {
    return m_name;
}
