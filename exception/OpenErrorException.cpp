#include "OpenErrorException.hpp"

OpenErrorException::OpenErrorException(char *message)
{
	this->message = message;
}

const char *OpenErrorException::what() const
{
	return this->message;
}
