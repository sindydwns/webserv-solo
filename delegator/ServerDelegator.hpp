#ifndef ServerDelegator_HPP
#define ServerDelegator_HPP

#include "Delegator.hpp"

class ServerDelegator : public Delegator
{
public:
	ServerDelegator(int kq);
	~ServerDelegator();

	virtual void run(struct kevent &event);

private:
};

#endif