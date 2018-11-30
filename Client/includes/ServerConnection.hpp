/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** ServerConnection.hpp
*/

#if !defined(_SERVERCONNECTION_HPP)
#define _SERVERCONNECTION_HPP

#include <mutex>
#include <memory>
#include <list>
#include "JsonBuilder/JsonBuilder.hpp"
#include "Network/UdpSocket/UdpSocket.hpp"
#include "Network/TcpSocket/TcpSocket.hpp"
#include "Network/GameProtocol.hpp"

namespace rtype {

class ServerConnection: private common::JsonBuilder {
public:
	ServerConnection(): JsonBuilder(_tcpSock) {}
	~ServerConnection();

	bool			connect(std::string	const &host, std::uint16_t port);

	json::Entity	login(std::string const &username);

	json::Entity	getSessions();
	json::Entity	makeSession(std::string const &name, int max = 4);
	json::Entity	joinSession(int sessionId);
	json::Entity	quitSession(int sessionId);

	void			run();
	void			stop();

	auto			isStarted() { return _isStarted; }
	std::list<std::shared_ptr<proto::PacketBase>>
					getAvailablePackets();
private:
	void			_sendJson(json::Entity const &obj);
	json::Entity	_getJson();

	void			_entryPoint();

	nw::TcpSocket	_tcpSock;
	nw::UdpSocket	_udpSock;
	nw::UdpEndpoint	_serverEp;
	nw::UdpEndpoint	_responseEp;

	std::list<std::shared_ptr<proto::PacketBase>>
					_availablePackets;
	std::mutex		_listMtx;

	bool			_isStarted = false;
	long			_id;
	std::string		_username;

	void			*_threadPtr = nullptr;
	bool			_continue = true;
};

}

#endif // _SERVERCONNECTION_HPP