#ifndef Delegator_HPP
#define Delegator_HPP

#include <sys/event.h>

class Delegator
{
public:
	Delegator(int kq, int fd);
	virtual ~Delegator();

	enum RunResult
	{
		Continue = 0,
		End = 1
	};

	virtual enum Delegator::RunResult run(struct kevent &event) = 0;


protected:
	int kq;
	int fd;
};

#endif