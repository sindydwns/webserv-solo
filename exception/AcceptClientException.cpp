#include "AcceptClientException.hpp"

AcceptClientException::AcceptClientException(char *message)
{
	this->message = message;
}

const char *AcceptClientException::what() const
{
	return this->message;
}
