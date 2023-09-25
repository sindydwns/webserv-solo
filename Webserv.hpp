#ifndef Webserv_HPP
#define Webserv_HPP

#include "vector"
#include "Config.hpp"

class Webserv
{
public:
	~Webserv();
	Webserv(const Config &config);

	void open();
	void loop();

private:
	Config config;

	std::vector<int> serverSockets;
	int kq;
};

#endif