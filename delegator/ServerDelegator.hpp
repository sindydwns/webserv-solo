#ifndef ServerDelegator_HPP
#define ServerDelegator_HPP

#include "Delegator.hpp"

class ServerDelegator : public Delegator
{
public:
	ServerDelegator();
	~ServerDelegator();
	ServerDelegator(const ServerDelegator &rhs);
	ServerDelegator &operator=(const ServerDelegator &rhs);
private:
};

#endif