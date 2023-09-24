#ifndef ClientDelegator_HPP
#define ClientDelegator_HPP

#include "Delegator.hpp"
#include "parser/ParseStream.hpp"

class ClientDelegator : public Delegator
{
public:
	ClientDelegator(int kq);

	virtual void run(struct kevent &event);

private:
	ParseStream stream;
	std::string res;
	size_t resIdx;
};

#endif
