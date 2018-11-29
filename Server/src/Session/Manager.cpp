/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** Manager.cpp
*/

#include <functional>
#include <mutex>
#include <chrono>
#include "Server.hpp"
#include "Session/Manager.hpp"
#include "Network/GameProtocol.hpp"

namespace rtype { namespace session {

Manager::Manager(std::uint32_t ticks):
		_sleepTime(1000 / ticks) {
	_port = _sock.makeMeAsListener();
	_sock.setNonBlocking(true);
	_thread = std::unique_ptr<std::thread>(new std::thread(&Manager::_entryPoint, this)); // Force start after mutex init
	std::cout << "Session manager listening on (udp): " << _port << std::endl;
}

Manager::~Manager() {
	_continue = false;
	_thread->join();
}

void	Manager::_entryPoint() {
	char 			buf[2048];
	nw::UdpBuffer 	recvBuffer(buf, sizeof(buf));
	nw::UdpEndpoint	ep;

	while (_continue) {
		std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
		start = std::chrono::high_resolution_clock::now();
		while (_sock.recvFrom(recvBuffer, ep) > 0) {
			auto &b = *reinterpret_cast<proto::PacketBase*>(buf);
			
			if (b.type == proto::Type::UDP_REGISTER) {
				auto 				playerId = reinterpret_cast<proto::UdpRegister*>(buf)->playerId();
				proto::UdpConfirm	confirm{proto::Type::UDP_CONFIRM, 0, 0, false};
				nw::UdpBuffer		resp{reinterpret_cast<char*>(&confirm), sizeof(confirm)};

				for (auto &clt: Server::instance().getUsers()) {
					if (clt._status.id == playerId) {
						clt._udpEndpoint = ep;
						clt._status.udpIsSetup = true;
						confirm.status = true;
						break;
					}
				}
				_sock.sendTo(resp, ep);
			} else {
				for (auto &s: _sessions) {
					if (s._id == b.sessionId()) {
						auto	*packet = reinterpret_cast<proto::PacketBase*>(::operator new(recvBuffer.len));
						memmove(packet, buf, recvBuffer.len);

						s.addTask([packet] () {
							return (std::shared_ptr<proto::PacketBase>(packet));
						});
						break;
					}
				}
			}

		
			recvBuffer.len = sizeof(buf);
		}
		end = std::chrono::high_resolution_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
		
		std::this_thread::sleep_for(std::chrono::milliseconds(_sleepTime - elapsed));
	}
}

static std::mutex	_generateIdMutex;
inline std::uint32_t	Manager::_generateId() {
	std::lock_guard<std::mutex>	_guard(_generateIdMutex);
	static std::uint32_t	counter = 0;

	return ++counter;
}

Session	&Manager::create(std::string const &name, int playerMax) {
	for (auto &s: _sessions) {
		if (s._name == name) {
			throw std::runtime_error("Name already in use");
		}
	}

	return _sessions.emplace_front(this, _generateId(), name, playerMax);
}

}}
