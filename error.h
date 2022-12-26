#ifndef CODE_ERROR_HPP
#define CODE_ERROR_HPP

//#include <string>
#include <exception>


class ErrorException : public std::exception {
public:
    explicit ErrorException(std::string message);

    std::string getMessage() const;

private:
    std::string message;
};

//------------------------------------------------------------------------------------------------

void error(std::string message);


ErrorException::ErrorException(std::string message) {
    this->message = message;
}

std::string ErrorException::getMessage() const {
    return message;
}

//----------------------------------------------------------------------------------------

void error(std::string message) {
    throw ErrorException(message);
}

#endif //CODE_ERROR_HPP
