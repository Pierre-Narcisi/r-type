/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** ServerConnection.cpp
*/

#include <thread>
#include <signal.h>
#include <sstream>
#include <iostream>
#include "Network/GameProtocol.hpp"
#include "Json/Entity.hpp"
#include "ServerConnection.hpp"

namespace rtype {

ServerConnection::~ServerConnection() {
	if (_threadPtr) {
		auto *t = reinterpret_cast<std::thread*>(_threadPtr);

		_continue = false;
		t->join();
		delete t;
	}
}

void	ServerConnection::stop() {
	_continue = false;

	if (_threadPtr) {
		auto *t = reinterpret_cast<std::thread*>(_threadPtr);
		
#if defined(_MSC_VER)
		TerminateThread(t->native_handle(), 0);
#else
		pthread_kill(t->native_handle(), SIGINT);
#endif
	}
}

inline void	ServerConnection::_sendJson(json::Entity const &obj) {
	std::ostringstream	sstm;
	
	obj.print(sstm, json::Entity::StringifyAttr::MINIFIED);
	
	std::string	buffer(sstm.str());
	_tcpSock.write(buffer.c_str(), buffer.length());
}

inline json::Entity	ServerConnection::_getJson() {
	bool	cont = true;

	while (cont) {
		auto lData = _extractJsonObjects(1000);

		if (lData.size() > 0) {
			cont = false;
			return lData.front();
		}
	}
}

bool	ServerConnection::connect(std::string const &host, std::uint16_t port) {
	_tcpSock.connect(nw::TcpEndpoint(host, port));

	if (_tcpSock.isConnected()) {
		auto resp = _getJson();

		std::cout << "[" << host << "]: " << resp["message"].to<std::string>() << std::endl;
		_serverEp = nw::UdpEndpoint(host, resp["sessionsPort"].to<int>());

		proto::UdpRegister	reg{proto::Type::UDP_REGISTER, 0, resp["id"].to<int>()};
		proto::UdpConfirm	conf{};
		nw::UdpBuffer		buf{reinterpret_cast<char*>(&conf), sizeof(conf)};

		_responseEp = _udpSock.sendTo({reinterpret_cast<char*>(&reg), sizeof(reg)}, _serverEp);
		_udpSock.recvFrom(buf, _responseEp);

		return conf.status;
	}
	return false;
}

json::Entity	ServerConnection::login(std::string const &username) {
	_sendJson(json::makeObject {
		{ "path", "login" },
		{ "username", username }
	});

	return _getJson();
}


json::Entity	ServerConnection::makeSession(std::string const &name, int max) {
	_sendJson(json::makeObject {
		{ "path", "session:create" },
		{ "name", name },
		{ "playerMax", max }
	});

	return _getJson();
}

json::Entity	ServerConnection::getSessions() {
	_sendJson(json::makeObject {
		{ "path", "session:list" }
	});

	return _getJson();
}

json::Entity	ServerConnection::joinSession(int sessionId) {
	_sendJson(json::makeObject {
		{ "path", "session:join" },
		{ "id", sessionId }
	});

	return _getJson();
}

json::Entity	ServerConnection::quitSession(int sessionId) {
	_sendJson(json::makeObject {
		{ "path", "session:quit" },
		{ "id", sessionId }
	});

	return _getJson();
}

void	ServerConnection::run() {
	_threadPtr = reinterpret_cast<void*>(
		new std::thread(std::bind(&ServerConnection::_entryPoint, this))
	);
}

void	ServerConnection::_entryPoint() {
	char	buf[2048];

	while (_continue) {
		auto			*p = reinterpret_cast<proto::PacketBase*>(buf); 
		nw::UdpBuffer	wbuf{buf, sizeof(buf)};

		_udpSock.recvFrom(wbuf, _responseEp);
		if (p->type == proto::Type::PING) {
			std::cout << "[server] PING" << std::endl;
		} else {
			auto sharedPtr = std::shared_ptr<proto::PacketBase>(
				reinterpret_cast<proto::PacketBase*>(::operator new(wbuf.len))
			);

			memmove(sharedPtr.get(), buf, wbuf.len);

			std::lock_guard<std::mutex>	_guard(_listMtx);
			_availablePackets.emplace_back(sharedPtr);
		}
	}
}

std::list<std::shared_ptr<proto::PacketBase>>	ServerConnection::getAvailablePackets() {
	std::lock_guard<std::mutex>	_guard(_listMtx);
	auto save = _availablePackets;

	_availablePackets.clear();
	return (save);
}

}