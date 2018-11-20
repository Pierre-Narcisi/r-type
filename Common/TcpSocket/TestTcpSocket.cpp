#include <iostream>


#include "TcpSocket.hpp"

int main(int ac, char **av) {
	if (ac > 2) {
		try {
			nw::TcpSocket	tcp;
			char buffer[256];

			nw::TcpEndpoint tcp_ep(av[1], std::atoi(av[2]));

			for (auto &ip: tcp_ep.getResolvedIps()) {
				std::cout << ip << std::endl;
			}

			tcp.connect(tcp_ep);
			
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