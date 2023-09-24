#ifndef Webserv_HPP
#define Webserv_HPP

#include "vector"
#include "Config.hpp"

class Webserv
{
public:
	Webserv();
	~Webserv();
	Webserv(const Webserv &rhs);
	Webserv &operator=(const Webserv &rhs);
	Webserv(const Config &config);

	void open();
	void loop();

private:
	Config config;
	void openSocket(int port);
	void closeAllSocket();

	std::vector<int> serverSockets;
	int kq;
};

#endif