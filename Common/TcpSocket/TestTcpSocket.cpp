#include <iostream>


#include "TcpSocket.hpp"

int main(int ac, char **av) {
	if (ac > 1) {
		try {
			nw::TcpSocket	tcp;
			char buffer[256];

			tcp.connect(nw::TcpEndpoint("localhost", std::atoi(av[1])));
			
			std::string s;
			std::cin >> s;
			tcp.write(s.c_str(), s.length());

			auto len = tcp.read(buffer, sizeof(buffer) - 1);
			std::cout << "len = " << len << std::endl;
			buffer[len] = 0;

			std::cout << "in: " << buffer << std::endl;
		} catch (std::exception &e) {
			std::cout << e.what() << std::endl;
		}
	}
	return (0);
}