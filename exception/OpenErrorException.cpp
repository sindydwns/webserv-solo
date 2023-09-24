#include "OpenErrorException.hpp"

OpenErrorException::OpenErrorException(const char *message)
{
	this->message = message;
}

const char *OpenErrorException::what() const _NOEXCEPT
{
	return this->message;
}
