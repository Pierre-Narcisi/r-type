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
#include "Router.hpp"

namespace rtype {

class Server;

class ClientConnection: public nw::TcpListenerSlave, public common::JsonBuider {
public:
	ClientConnection(int socketFd, nw::TcpListenerSlave::NativeAddr const &addr);
	~ClientConnection() {
		_onDestroy.fire();
	}

	virtual void	onDataAvailable(std::size_t available) final;
private:
	void	_sendJson(json::Entity const &rep);
	void	_routerInit();

	void	_login(json::Entity &req, json::Entity &res);

	struct {
		bool		logged = false;
		std::string	username;
	}		_status;

	Router		_router;
	evt::Event	_onDestroy;

	friend Server;
};

}

#endif // _CLIENTCONNECTION_HPP
