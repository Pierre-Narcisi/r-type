/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** ClientConnection.hpp
*/

#if !defined(_CLIENTCONNECTION_HPP)
#define _CLIENTCONNECTION_HPP

#include "JsonBuilder/JsonBuilder.hpp"
#include "TcpListenerSlave.hpp"
#include "Router.hpp"

namespace rtype {

class ClientConnection: public nw::TcpListenerSlave, public common::JsonBuider {
public:
	ClientConnection(int socketFd, nw::TcpListenerSlave::NativeAddr const &addr);

	virtual void	onDataAvailable(std::size_t available) final;
private:
	void	_sendJson(json::Entity const &rep);
	void	_routerInit();

	void	_login(json::Entity &req, json::Entity &res);

	Router	_router;
};

}

#endif // _CLIENTCONNECTION_HPP
