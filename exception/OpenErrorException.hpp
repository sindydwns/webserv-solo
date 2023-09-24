#ifndef OpenErrorException_HPP
#define OpenErrorException_HPP

#include <exception>

class OpenErrorException : public std::exception {
public:
	OpenErrorException(char *message);
	virtual const char* what() const _NOEXCEPT;
private:
	char *message;
};

#endif