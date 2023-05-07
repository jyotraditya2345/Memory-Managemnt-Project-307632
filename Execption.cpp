#ifndef MY_EXCEPTION_H
#define MY_EXCEPTION_H

#include <exception>
#include <string>

class MyException : public std::exception {
public:
    MyException(const std::string& message) : message_(message) {}
    virtual const char* what() const throw() {
        return message_.c_str();
    }
private:
    std::string message_;
};

#endif
