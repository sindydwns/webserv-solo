#include <iostream>
#include "Config.hpp"
#include "Webserv.hpp"

int main() {
	Config config;
	Webserv server(config);
	try {
		server.open();
		server.loop();
	} catch(std::exception &e) {
		std::cout << e.what() << std::endl;
	}
}
