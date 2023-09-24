#ifndef OpenErrorException_HPP
#define OpenErrorException_HPP

#include <exception>

class OpenErrorException : public std::exception {
public:
	OpenErrorException(const char *message);
	virtual const char* what() const _NOEXCEPT;
private:
	const char *message;
};

#endif