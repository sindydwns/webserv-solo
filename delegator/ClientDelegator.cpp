#include "ClientDelegator.hpp"
#include "HttpRequestParser.hpp"
#include "Singleton.hpp"

ClientDelegator::ClientDelegator(int kq): Delegator(kq)
{
	this->stream = Singleton<HttpRequestParser>::getInstance()->makeStream();
}

void ClientDelegator::run(struct kevent &event)
{
	(void)event;
}
