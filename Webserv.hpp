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

	std::vector<int> serverSockets;
	int kq;
};

#endif