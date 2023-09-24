#include "ServerDelegator.hpp"
#include "ClientDelegator.hpp"
#include "../exception/OpenErrorException.hpp"
#include "../exception/AcceptClientException.hpp"

#include <netdb.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/event.h>

ServerDelegator::ServerDelegator(int kq, int port): Delegator(kq)
{
	int serverSocket;
    struct sockaddr_in address;

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket == -1) throw OpenErrorException("server open fail: socket");

	int opt = 1;
	if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int))) {
		throw OpenErrorException("server open fail: setsockopt");
	}

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(serverSocket, (struct sockaddr *)&address, sizeof(address))) {
		throw OpenErrorException("server open fail: bind");
	}
    if (listen(serverSocket, 3)) {
		throw OpenErrorException("server open fail: listen");
	}

	struct kevent serverEvent;
	EV_SET(&serverEvent, serverSocket, EVFILT_READ, EV_ADD, 0, 0, this);
	kevent(kq, &serverEvent, 1, NULL, 0, NULL);
}

ServerDelegator::~ServerDelegator()
{
	close(this->fd);
}

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
