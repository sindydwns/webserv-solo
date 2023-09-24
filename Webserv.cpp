#include "Webserv.hpp"

// socket
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

// for kqueue
#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>

Webserv::Webserv() {}
Webserv::Webserv(const Webserv &rhs) { (void)rhs; }
Webserv &Webserv::operator=(const Webserv &rhs) { (void)rhs; return *this; }
Webserv::~Webserv() {}
Webserv::Webserv(const Config &config): config(config) {}

// for delegator
#include "delegator/Delegator.hpp"
#include "delegator/ServerDelegator.hpp"

// exception
#include "exception/OpenErrorException.hpp"

void Webserv::open()
{
	std::vector<int> ports;
	ports.push_back(8080);

	if (ports.size() == 0) {
		throw OpenErrorException("server open fail: undefined port");
	}

	for (size_t i = 0; i < ports.size(); i++) {
		try {
			openSocket(ports[i]);
		} catch (std::exception &e) {
			closeAllSocket();
			throw e;
		}
	}

	this->kq = kqueue();
	struct kevent serverEvent[serverSockets.size()];
	for (size_t i = 0; i < serverSockets.size(); i++) {
		Delegator *server = new ServerDelegator(this->kq, serverSockets[i]);
		EV_SET(serverEvent + i, serverSockets[i], EVFILT_READ, EV_ADD, 0, 0, server);
	}
	kevent(kq, serverEvent, serverSockets.size(), NULL, 0, NULL);
}

void Webserv::loop()
{
	while (1) {
		struct kevent eventList[1024];
		int nev = kevent(kq, NULL, 0, eventList, 1024, NULL);
		for (int i = 0; i < nev; i++) {
			Delegator *delegator = reinterpret_cast<Delegator*>(eventList[i].udata);
			Delegator::RunResult res = delegator->run(eventList[i]);
			if (res == Delegator::End) {
				delete delegator;
			}
		}
	}
}

void Webserv::openSocket(int port)
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
	serverSockets.push_back(serverSocket);
}

void Webserv::closeAllSocket()
{
	for (size_t i = 0; i < serverSockets.size(); i++) {
		close(serverSockets[i]);
	}
}
