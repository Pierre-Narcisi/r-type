/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** ClientConnection.hpp
*/


#if !defined(_CLIENTCONNECTION_HPP)
#define _CLIENTCONNECTION_HPP

#include "TcpListener.hpp"

namespace rtype {

class ClientConnection: public nw::TcpListenerSalve {
public:
	ClientConnection(int socketFd, nw::TcpListenerSalve::NativeAddr const &addr);

	virtual void	onDataAvailable() final;
private:
};

}

#endif // _CLIENTCONNECTION_HPP
