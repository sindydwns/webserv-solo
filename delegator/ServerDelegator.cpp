#include "ServerDelegator.hpp"
#include "ClientDelegator.hpp"
#include "../exception/AcceptClientException.hpp"

#include <netdb.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/event.h>

ServerDelegator::ServerDelegator(int kq, int fd): Delegator(kq, fd) { }
ServerDelegator::~ServerDelegator() { }

Delegator::RunResult ServerDelegator::run(struct kevent &event)
{
    struct sockaddr_in address;
	size_t addrlen = sizeof(address);
	int fd = event.ident;

	int clientSocket = accept(fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
	if (clientSocket == -1) {
		throw AcceptClientException("client accept fail: accept");
	}

	fcntl(clientSocket, F_SETFL, O_NONBLOCK);
	
	ClientDelegator *client = new ClientDelegator(this->kq, clientSocket);
	struct kevent clientEvent;
	EV_SET(&clientEvent, clientSocket, EVFILT_READ, EV_ADD, 0, 0, client);
	kevent(this->kq, &clientEvent, 1, NULL, 0, NULL);

	return Continue;
}
