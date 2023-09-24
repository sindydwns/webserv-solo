#ifndef AcceptClientException_HPP
#define AcceptClientException_HPP

#include <exception>

class AcceptClientException : public std::exception {
public:
	AcceptClientException(char *message);
	virtual const char* what() const _NOEXCEPT;
private:
	char *message;
};

#endif