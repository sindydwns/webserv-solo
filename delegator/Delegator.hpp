#ifndef Delegator_HPP
#define Delegator_HPP

#include <sys/event.h>

class Delegator
{
public:
	Delegator(int kq);
	virtual ~Delegator();

	virtual void run(struct kevent &event) = 0;

protected:
	int kq;
};

#endif