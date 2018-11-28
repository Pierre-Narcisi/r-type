/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** ClientConnection.hpp
*/

#if !defined(_CLIENTCONNECTION_HPP)
#define _CLIENTCONNECTION_HPP

#include "Event/Event.hpp"
#include "JsonBuilder/JsonBuilder.hpp"
#include "TcpListenerSlave.hpp"
#include "Event/Manager.hpp"
#include "Router.hpp"

namespace rtype {

class Server;

class ClientConnection: public nw::TcpListenerSlave, public common::JsonBuilder {
public:
	ClientConnection(int socketFd, nw::TcpListenerSlave::NativeAddr const &addr);
	~ClientConnection() {
		evt::Manager::get()["onPlayerDisconnect"]->fire<void, ClientConnection&>(*this);
	}
	ClientConnection(ClientConnection const &) = delete;
	ClientConnection(ClientConnection&&) = default;
	ClientConnection &operator=(ClientConnection&) = delete;

	virtual void	onDataAvailable(std::size_t available) final;
private:
	void	_sendJson(json::Entity const &rep);
	void	_routerInit();

	void	_login(json::Entity &req, json::Entity &resp);
	void	_createSession(json::Entity &req, json::Entity &resp);

	struct {
		bool		logged = false;
		std::string	username;
	}		_status;

	Router		_router;

	friend Server;
};

}

#endif // _CLIENTCONNECTION_HPP
