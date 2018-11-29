#pragma once

#include <string>

class Exception {
public:
    explicit Exception(const std::string & msg) : m_msg(msg){}
    ~Exception(){}
    const std::string & what() const {
        return m_msg;
    }
private:
    std::string m_msg;
};
