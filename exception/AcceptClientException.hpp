#ifndef AcceptClientException_HPP
#define AcceptClientException_HPP

#include <exception>

class AcceptClientException : public std::exception {
public:
	AcceptClientException(const char *message);
	virtual const char* what() const _NOEXCEPT;
private:
	const char *message;
};

#endif