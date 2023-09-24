#ifndef ClientDelegator_HPP
#define ClientDelegator_HPP

#include <unistd.h>
#include "Delegator.hpp"
#include "../parser/ParseStream.hpp"

#define BUFFER_SIZE 42

class ClientDelegator : public Delegator
{
public:
	ClientDelegator(int kq, int fd);

	virtual enum Delegator::RunResult run(struct kevent &event);

private:
	ParseStream stream;
	std::string res;
	size_t resIdx;
};

#endif
