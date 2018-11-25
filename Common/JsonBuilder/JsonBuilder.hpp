/*
** EPITECH PROJECT, 2018
** r-type
** File description:
** JsonBuilder.hpp
*/


#if !defined(_JSONBUILDER_HPP)
#define _JSONBUILDER_HPP

#include <list>
#include "Json/Parser.hpp"
#include "Network/TcpSocket/TcpSocket.hpp"

namespace common {

class JsonBuider {
public:
	JsonBuider(nw::TcpSocket &socket): _socket(socket) {}
protected:
	std::list<json::Entity>	_extractJsonObjects(std::size_t available);

	std::function<void(json::Parser::ParserException const &e)>	_onIllegalJson;
private:
	nw::TcpSocket		&_socket;
	std::vector<char>	_buffer;
};

}

#endif // _JSONBUILDER_HPP
