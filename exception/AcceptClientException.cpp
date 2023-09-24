#include "AcceptClientException.hpp"

AcceptClientException::AcceptClientException(const char *message)
{
	this->message = message;
}

const char *AcceptClientException::what() const _NOEXCEPT
{
	return this->message;
}
