#ifndef ServerDelegator_HPP
#define ServerDelegator_HPP

#include "Delegator.hpp"

class ServerDelegator : public Delegator
{
public:
	ServerDelegator(int kq, int fd);
	~ServerDelegator();

	virtual enum Delegator::RunResult run(struct kevent &event);

private:
};

#endif