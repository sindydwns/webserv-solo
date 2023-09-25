#include <iostream>
#include "Webserv.hpp"

// socket
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

// for kqueue
#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>

static void sigpipe(int sig)
{
	std::cout << "test: " << sig << std::endl;
}

Webserv::~Webserv() {}
Webserv::Webserv(const Config &config): config(config)
{
	signal(SIGPIPE, sigpipe);
}

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

	this->kq = kqueue();
	std::vector<ServerDelegator*> servers;
	for (size_t i = 0; i < ports.size(); i++) {
		try {
			ServerDelegator *server = new ServerDelegator(kq, ports[i]);
			servers.push_back(server);
		} catch (std::exception &e) {
			for (size_t k = 0; k < i; k++) {
				delete servers[k];
			}
			throw e;
		}
	}

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
		std::vector<Delegator*> deleteList;
		for (int i = 0; i < nev; i++) {
			try {
				Delegator *delegator = reinterpret_cast<Delegator*>(eventList[i].udata);
				Delegator::RunResult res = delegator->run(eventList[i]);
				if (res == Delegator::End || res == Delegator::RecvEOF || res == Delegator::TimeOver) {
					deleteList.push_back(delegator);;
				}
			} catch(std::exception &e) {
				std::cout << e.what() << std::endl;
			}
		}
		for (size_t i = 0; i < deleteList.size(); i++) {
			delete deleteList[i];
		}
	}
}
