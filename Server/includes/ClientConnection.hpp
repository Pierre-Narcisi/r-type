/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** ClientConnection.hpp
*/

#if !defined(_CLIENTCONNECTION_HPP)
#define _CLIENTCONNECTION_HPP

#include "TcpListenerSlave.hpp"

namespace rtype {

class ClientConnection: public nw::TcpListenerSlave {
public:
	ClientConnection(int socketFd, nw::TcpListenerSlave::NativeAddr const &addr);

	virtual void	onDataAvailable(std::size_t available) final;
private:
};

}

#endif // _CLIENTCONNECTION_HPP
