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
	_continue = false;
	//stop();
}

void	ServerConnection::stop() {
	_continue = false;

	if (_threadPtr) {
		auto *t1 = reinterpret_cast<std::thread*>(_threadPtr);
		auto *t2 = reinterpret_cast<std::thread*>(_threadTasksPtr);
		
#if defined(_MSC_VER)
		TerminateThread(t1->native_handle(), 0);
		TerminateThread(t2->native_handle(), 0);
#else
		pthread_kill(t1->native_handle(), SIGINT);
		pthread_kill(t2->native_handle(), SIGINT);
#endif
		t1->join();
		t2->join();
	}
}

inline void	ServerConnection::_sendJson(json::Entity const &obj) {
	std::ostringstream	sstm;
	
	obj.print(sstm, json::Entity::StringifyAttr::MINIFIED);
	
	std::string	buffer(sstm.str());
	_tcpSock.write(buffer.c_str(), SOCK_BUFFER_LEN_TYPE(buffer.length()));
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
	return json::Entity();
}

bool	ServerConnection::connect(std::string const &host, std::uint16_t port) {
	_tcpSock.connect(nw::TcpEndpoint(host, port));

	if (_tcpSock.isConnected()) {
		auto resp = _getJson();

		_id = resp["id"].to<int>();

		std::cout << "[" << host << "]: " << resp["message"].to<std::string>() << std::endl;
		_serverEp = nw::UdpEndpoint(host, resp["sessionsPort"].to<int>());

		proto::UdpRegister	reg{proto::Type::UDP_REGISTER, 0, (std::int32_t)resp["id"].to<int>()};
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
		{ "sessionId", sessionId }
	});

	return _getJson();
}

json::Entity	ServerConnection::quitSession(int sessionId) {
	_sendJson(json::makeObject {
		{ "path", "session:quit" },
		{ "sessionId", sessionId }
	});

	return _getJson();
}

void	ServerConnection::updateGame(int sessionId, std::function<void(json::Entity)> const callback) {
	std::lock_guard<std::mutex>	_guard(_tasksMtx);
	_tasks.push_back([this, sessionId, callback] {
		_sendJson(json::makeObject {
			{ "path", "session:update" },
			{ "sessionId", sessionId }
		});

		callback(_getJson());
	});
}

void	ServerConnection::run() {
	_threadPtr = reinterpret_cast<void*>(
		new std::thread(std::bind(&ServerConnection::_entryPoint, this))
	);
	_threadTasksPtr = reinterpret_cast<void*>(
		new std::thread(std::bind(&ServerConnection::_entryPointTasks, this))
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
			//std::cout << "[server] " << (int) p->type << std::endl;
			auto sharedPtr = std::shared_ptr<proto::PacketBase>(
				reinterpret_cast<proto::PacketBase*>(::operator new(wbuf.len))
			);

			memmove(sharedPtr.get(), buf, wbuf.len);

			std::lock_guard<std::mutex>	_guard(_listMtx);
			_availablePackets.emplace_back(sharedPtr);
		}
	}
}

void	ServerConnection::_entryPointTasks() {
	while (_continue) {
		decltype(_tasks)::value_type	task;
		{
			std::lock_guard<std::mutex>	_guard(_tasksMtx);
			if (_tasks.size()) {
				task = _tasks.front();
				_tasks.pop_front();
			}
		}
		if (task != nullptr) task();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

std::list<std::shared_ptr<proto::PacketBase>>	ServerConnection::getAvailablePackets() {
	std::lock_guard<std::mutex>	_guard(_listMtx);
	auto save = _availablePackets;

	_availablePackets.clear();
	return (save);
}

}