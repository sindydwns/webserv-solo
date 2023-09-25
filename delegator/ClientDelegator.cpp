#include <sys/socket.h>
#include "ClientDelegator.hpp"
#include "../HttpRequestParser.hpp"
#include "../Singleton.hpp"

ClientDelegator::ClientDelegator(int kq, int fd): Delegator(kq), fd(fd), resIdx(0)
{
	this->stream = Singleton<HttpRequestParser>::getInstance()->makeStream();
}

ClientDelegator::~ClientDelegator()
{
	std::cout << fd << " closed" << std::endl;
	close(this->fd);
}

Delegator::RunResult ClientDelegator::run(struct kevent &event)
{
	if (event.filter == EVFILT_READ) {
		char buffer[BUFFER_SIZE] = {0};
		memset(buffer, 0, BUFFER_SIZE);
		int valread = read(fd, buffer, BUFFER_SIZE - 1);
		if (valread > 0) {
			std::string buff = std::string(buffer);
			if (this->stream.next(buff) == false) {
				this->res = "HTTP/1.1 200 OK\n";
				if (this->stream.isState(VALID)) {
					std::stringstream ss;
					std::string str = this->stream.getResult().toString();
					ss << "Content-Type: text/html\n";
					ss << "Content-Length: " << str.size() << "\n";
					ss << "Connection: keep-alive\n";
					this->res += ss.str();
					this->res += "\r\n";
					this->res += str;
				}
				if (this->stream.isState(INVALID)) {
					std::stringstream ss;
					std::string str = "req is invalid\n";
					ss << "Content-Type: text/html\n";
					ss << "Content-Length: " << str.size() << "\n";
					ss << "Connection: keep-alive\n";
					this->res += "\r\n";
					this->res += str;
				}
				struct kevent clientEvent;
				EV_SET(&clientEvent, fd, EVFILT_READ, EV_DELETE, 0, 0, this);
				EV_SET(&clientEvent, fd, EVFILT_WRITE, EV_ADD, 0, 0, this);
				kevent(kq, &clientEvent, 1, NULL, 0, NULL);
			}
		}
		std::cout << fd << ": " << buffer << "[" << valread << "]" << std::endl;
		if (valread == 0) {			
			return RecvEOF;
		}
	}
	if (event.filter == EVFILT_WRITE) {
		std::string &res = this->res;
		if (res.size() - this->resIdx > 0) {
			size_t i = this->resIdx;
			ssize_t written = send(fd, &(res.at(i)), res.size() - i, 0);
			if (written > 0) this->resIdx += written;
		}
		if (res.size() == this->resIdx) {
			struct kevent clientEvent;
			EV_SET(&clientEvent, fd, EVFILT_WRITE, EV_DELETE, 0, 0, this);
			kevent(kq, &clientEvent, 1, NULL, 0, NULL);
		}
	}

	if (event.filter == EVFILT_TIMER) {
		return TimeOver;
	}
	return Continue;
}
